/******************************************************************************
 *
 *  Copyright 2018 NXP
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#include "eSEClientIntf.h"
#include <cutils/log.h>
#include <dirent.h>
#include <stdlib.h>
#include <pthread.h>
#include <IChannel.h>
#include <JcDnld.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <phNxpConfig.h>
#include "phNxpConfig.h"
#include <android-base/logging.h>
#include <android-base/stringprintf.h>

bool nfc_debug_enabled;
void* performJCOS_Download_thread(void* data);
IChannel_t Ch;
static const char *path[3] = {"/data/vendor/nfc/JcopOs_Update1.apdu",
                             "/data/vendor/nfc/JcopOs_Update2.apdu",
                             "/data/vendor/nfc/JcopOs_Update3.apdu"};

static const char *uai_path[2] = {"/data/vendor/nfc/cci.jcsh",
                                  "/data/vendor/nfc/jci.jcsh"};
static const char *isSystemImgInfo = "/data/vendor/nfc/jcop_info.txt";
static const char *lsUpdateBackupPath =
"/data/vendor/secure_element/loaderservice_updater.txt";
static const char *isFirstTimeLsUpdate =
"/data/vendor/secure_element/LS_Status.txt";
se_extns_entry seExtn;

/*******************************************************************************
**
** Function:        checkeSEClientUpdateRequired
**
** Description:     HAL service entry criteria is verified 
**                  Read the interface and condition for ese Update(JCOP download/LS download)
**                  from the config file and file path and validate.
**
** Returns:         SUCCESS of ok
**
*******************************************************************************/
uint8_t checkeSEClientRequired( ) {
  uint8_t status = SESTATUS_FAILED;
  unsigned long int num;
  bool isApduPresent = true;
  bool isSystemImgUpdated = true;
  bool isLsScriptPresent = true;
  bool isFirstLsUpdate = true;
  struct stat st;

  LOG(ERROR) <<"Check_HalStart_Entry: enter:  ";
  /*Check APDU files are present*/
  for (int num = 0; num < 2; num++)
  {
    if (stat(uai_path[num], &st))
    {
      isApduPresent = false;
    }
  }
  /*If UAI specific files are present*/
  if(isApduPresent == true)
  {
    for (int num = 0; num < 1; num++)
    {
      if (stat(path[num], &st))
      {
        isApduPresent = false;
      }
    }
  }
  /*Check if system image is updated*/
  if(stat(isSystemImgInfo, &st))
  {
    isSystemImgUpdated = false;
  }
  /*Check if LS script present*/
  if(stat(lsUpdateBackupPath, &st))
  {
	  isLsScriptPresent = false;
  }
  /*Check if it is first time LS update*/
  if(stat(isFirstTimeLsUpdate, &st))
  {
	  isFirstLsUpdate = false;
  }

  if(GetNxpNumValue(NAME_NXP_P61_JCOP_DEFAULT_INTERFACE, &num, sizeof(num))) {
    seExtn.sJcopUpdateIntferface = num; 
  }
  if(GetNxpNumValue(NAME_NXP_P61_LS_DEFAULT_INTERFACE, &num, sizeof(num))) {
	  seExtn.sLsUpdateIntferface = num; 
  }
  if(GetNxpNumValue(NAME_NXP_LS_FORCE_UPDATE_REQUIRED, &num, sizeof(num))) {
    seExtn.isLSUpdateRequired = num; 
  }
  if(GetNxpNumValue(NAME_NXP_JCOP_FORCE_UPDATE_REQUIRED, &num, sizeof(num))) {
    seExtn.isJcopUpdateRequired = num; 
  }
  if(isApduPresent && seExtn.sJcopUpdateIntferface &&
    (isSystemImgUpdated || seExtn.isJcopUpdateRequired))
  {
	LOG(ERROR) <<" Jcop update required  ";
    seExtn.isJcopUpdateRequired = true;
  }
  else
  {
	  LOG(ERROR) <<"Jcop update not required  ";
    seExtn.isJcopUpdateRequired = false;
  }

  if(isLsScriptPresent && seExtn.sLsUpdateIntferface &&
    (seExtn.isLSUpdateRequired || isFirstLsUpdate))
  {
	  LOG(ERROR) <<" LS update required  ";
    seExtn.isLSUpdateRequired = true;
  }
  else
  {
	  LOG(ERROR) <<" LS update not required  ";
    seExtn.isLSUpdateRequired = false;
  }
  return status;
}

uint8_t getJcopUpdateRequired()
{
  return seExtn.isJcopUpdateRequired;
}
uint8_t getLsUpdateRequired()
{
  return seExtn.isLSUpdateRequired;
}
uint8_t getJcopUpdateIntf()
{
  return seExtn.sJcopUpdateIntferface;
}
uint8_t getLsUpdateIntf()
{
  return seExtn.sLsUpdateIntferface;
}

