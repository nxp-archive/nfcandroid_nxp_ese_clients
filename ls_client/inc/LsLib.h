/*******************************************************************************
 *
 *  Copyright 2018-2019 NXP
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
 *****************************************************************************/

#ifndef LSC_H_
#define LSC_H_

#define NXP_LS_AID
#include "LsClient.h"
#include <stdio.h>
#include "../../inc/IChannel.h"
#include "phNxpConfig.h"

typedef struct Lsc_ChannelInfo {
  uint8_t channel_id;
  bool isOpend;
} Lsc_ChannelInfo_t;

typedef struct Lsc_TranscieveInfo {
  int32_t timeout;
  uint8_t sRecvData[1024];
  uint8_t sSendData[1024];
  int32_t sSendlength;
  int sRecvlength;
  uint8_t sTemp_recvbuf[1024];
} Lsc_TranscieveInfo_t;

typedef struct Lsc_ImageInfo {
  FILE* fp;
  int fls_size;
  char fls_path[384];
  int bytes_read;
  FILE* fResp;
  int fls_RespSize;
  char fls_RespPath[384];
  int bytes_wrote;
  Lsc_ChannelInfo_t Channel_Info[10];
  uint8_t channel_cnt;
  bool isUpdaterMode;
} Lsc_ImageInfo_t;
typedef enum {
  LS_Default = 0x00,
  LS_Cert = 0x7F21,
  LS_Sign = 0x60,
  LS_Comm = 0x40
} Ls_TagType;

typedef struct Lsc_lib_Context {
  IChannel_t            *mchannel;
  Lsc_ImageInfo_t Image_info;
  Lsc_TranscieveInfo_t Transcv_Info;
} Lsc_Dwnld_Context_t, *pLsc_Dwnld_Context_t;

typedef struct phNxpLs_data {
  uint32_t len;    /*!< length of the buffer */
  uint8_t* p_data; /*!< pointer to a buffer */
} phNxpLs_data;


static uint8_t OpenChannel[] = {0x00, 0x70, 0x00, 0x00, 0x01};
static uint8_t GetData[] = {0x80, 0xCA, 0x00, 0x46, 0x00};
#ifndef NXP_LS_AID
static uint8_t SelectLsc[] = {0x00, 0xA4, 0x04, 0x00, 0x0D, 0xA0,
                              0x00, 0x00, 0x03, 0x96, 0x41, 0x4C,
                              0x41, 0x01, 0x43, 0x4F, 0x52, 0x01};
#else
static uint8_t SelectLsc[] = {0xA4, 0x04, 0x00, 0x0E, 0xA0, 0x00,
                              0x00, 0x03, 0x96, 0x54, 0x43, 0x00, 0x00,
                              0x00, 0x01, 0x00, 0x0B, 0x00};

static const uint8_t SelectSEMS[] = {0xA4, 0x04, 0x00, 0x0D, 0xA0, 0x00,
                                    0x00, 0x01, 0x51, 0x53, 0x45, 0x4D,
                                    0x53, 0x00, 0x00, 0x00, 0x01};

static const uint8_t SelectSEMSUpdater[] = {0xA4, 0x04, 0x00, 0x0D, 0xA0, 0x00,
                                    0x00, 0x01, 0x51, 0x53, 0x45, 0x4D,
                                    0x53, 0xFF, 0xFF, 0xFF, 0x01};
#endif

/*LSC2*/
#define NOOFAIDS 0x03
#define LENOFAIDS 0x16
#define NUM_LS_AIDS 0x03
#define LEN_LS_AID 0x16
#define LS_SELF_UPDATE_AID_IDX 2
#ifndef NXP_LS_AID
static uint8_t ArrayOfAIDs[NUM_LS_AIDS][LEN_LS_AID] = {
    {0x12, 0x00, 0xA4, 0x04, 0x00, 0x0D, 0xA0, 0x00, 0x00, 0x03, 0x96, 0x41,
     0x4C, 0x41, 0x01, 0x4C, 0x44, 0x52, 0x01, 0x00, 0x00, 0x00},
    {0x12, 0x00, 0xA4, 0x04, 0x00, 0x0D, 0xA0, 0x00, 0x00, 0x03, 0x96, 0x41,
     0x4C, 0x41, 0x01, 0x43, 0x4F, 0x52, 0x01, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#else
static uint8_t ArrayOfAIDs[NOOFAIDS][LENOFAIDS] = {
    {0x14, 0x00, 0xA4, 0x04, 0x00, 0x0F, 0xA0, 0x00, 0x00, 0x03, 0x96, 0x54,
     0x43, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0B, 0x00, 0x02, 0x00},
    {0x14, 0x00, 0xA4, 0x04, 0x00, 0x0F, 0xA0, 0x00, 0x00, 0x03, 0x96, 0x54,
     0x43, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0B, 0x00, 0x01, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#endif
#define TAG_CERTIFICATE 0x7F21
#define TAG_LSES_RESP 0x4E
#define TAG_LSES_RSPLEN 0x02
#define TAG_SERIAL_NO 0x93
#define TAG_LSRE_ID 0x42
#define TAG_LSRE_SIGNID 0x45
#define TAG_CERTFHOLD_ID 0x5F20
#define TAG_KEY_USAGE 0x95
#define TAG_EFF_DATE 0x5F25
#define TAG_EXP_DATE 0x5F24
#define TAG_CCM_PERMISSION 0x53
#define TAG_SIG_RNS_COMP 0x5F37
#define MAX_META_STRING_SIZE 0xFF

#define TAG_LS_VER1 0x9F
#define TAG_LS_VER2 0x08
#define LS_DEFAULT_STATUS 0x6340
#define LS_SUCCESS_STATUS 0x9000
#define TAG_RE_KEYID 0x65

#define LS_ABORT_SW1 0x69
#define LS_ABORT_SW2 0x87
//#define AID_MEM_PATH "/data/vendor/secure_element/AID_MEM.txt"
//#define LS_STATUS_PATH "/data/vendor/secure_element/LS_Status.txt"
#define LS_SRC_BACKUP "/data/vendor/secure_element/LS_Src_Backup.txt"
#define LS_DST_BACKUP "/data/vendor/secure_element/LS_Dst_Backup.txt"
#define MAX_CERT_LEN (255 + 137)

/*LSC2*/

#define JCOP3_WR
#define MAX_SIZE 0xFF
#define PARAM_P1_OFFSET 0x02
#define FIRST_BLOCK 0x05
#define LAST_BLOCK 0x84
#define ONLY_BLOCK 0x85
#define CLA_BYTE 0x80
#define JSBL_HEADER_LEN 0x03
#define LSC_CMD_HDR_LEN 0x02

/* Definations for TAG ID's present in the script file*/
#define TAG_SELECT_ID 0x6F
#define TAG_LSC_ID 0x84
#define TAG_PRO_DATA_ID 0xA5
#define TAG_JSBL_HDR_ID 0x60
#define TAG_JSBL_KEY_ID 0x61
#define TAG_SIGNATURE_ID 0x41
#define TAG_LSC_CMD_ID 0x40
#define TAG_JSBL_CER_ID 0x44

/*Definitions for Install for load*/
#define INSTAL_LOAD_ID 0xE6
#define LOAD_CMD_ID 0xE8
#define LOAD_MORE_BLOCKS 0x00
#define LOAD_LAST_BLOCK 0x80

#define STORE_DATA_CLA 0x80
#define STORE_DATA_INS 0xE2
#define STORE_DATA_LEN 32
#define STORE_DATA_TAG 0x4F
static const char *AID_MEM_PATH[2] = {"/data/vendor/nfc/AID_MEM.txt",
                                  "/data/vendor/secure_element/AID_MEM.txt"};
static const char *LS_STATUS_PATH[2] = {"/data/vendor/nfc/LS_Status.txt",
                                  "/data/vendor/secure_element/LS_Status.txt"};

/*******************************************************************************
**
** Function:        initialize
**
** Description:     Initialize all member variables.
**                  native: Native data.
**
** Returns:         True if ok.
**
*******************************************************************************/
bool    initialize (IChannel_t *channel);

/*******************************************************************************
**
** Function:        finalize
**
** Description:     Release all resources.
**
** Returns:         None
**
*******************************************************************************/
void finalize();

/*******************************************************************************
**
** Function:        Perform_LSC
**
** Description:     Performs the LSC download sequence
**
** Returns:         Success if ok.
**
*******************************************************************************/
tLSC_STATUS Perform_LSC(const char* path, const char* dest,
                        const uint8_t* pdata, uint16_t len, uint8_t* respSW);

/*******************************************************************************
**
** Function:        LSC_OpenChannel
**
** Description:     Creates the logical channel with lsc
**
** Returns:         Success if ok.
**
*******************************************************************************/
static tLSC_STATUS LSC_OpenChannel(Lsc_ImageInfo_t* pContext,
                                   tLSC_STATUS status,
                                   Lsc_TranscieveInfo_t* pInfo)
    __attribute__((unused));

/*******************************************************************************
**
** Function:        LSC_SelectLsc
**
** Description:     Creates the logical channel with lsc
**                  Channel_id will be used for any communication with Lsc
**
** Returns:         Success if ok.
**
*******************************************************************************/
static tLSC_STATUS LSC_SelectLsc(Lsc_ImageInfo_t* pContext, tLSC_STATUS status,
                                 Lsc_TranscieveInfo_t* pInfo)
    __attribute__((unused));

/*******************************************************************************
**
** Function:        LSC_StoreData
**
** Description:     It is used to provide the LSC with an Unique
**                  Identifier of the Application that has triggered the LSC
*script.
**
** Returns:         Success if ok.
**
*******************************************************************************/
static tLSC_STATUS LSC_StoreData(Lsc_ImageInfo_t* pContext, tLSC_STATUS status,
                                 Lsc_TranscieveInfo_t* pInfo)
    __attribute__((unused));

/*******************************************************************************
**
** Function:        LSC_loadapplet
**
** Description:     Reads the script from the file and sent to Lsc
**
** Returns:         Success if ok.
**
*******************************************************************************/
static tLSC_STATUS LSC_loadapplet(Lsc_ImageInfo_t* Os_info, tLSC_STATUS status,
                                  Lsc_TranscieveInfo_t* pTranscv_Info)
    __attribute__((unused));

/*******************************************************************************
**
** Function:        LSC_update_seq_handler
**
** Description:     Performs the LSC update sequence handler sequence
**
** Returns:         Success if ok.
**
*******************************************************************************/
static tLSC_STATUS LSC_update_seq_handler(
    tLSC_STATUS (*seq_handler[])(Lsc_ImageInfo_t* pContext, tLSC_STATUS status,
                                 Lsc_TranscieveInfo_t* pInfo),
    const char* name, const char* dest) __attribute__((unused));

/*******************************************************************************
**
** Function:        Write_Response_To_OutFile
**
** Description:     Write the response to Out file
**                  with length recvlen from buffer RecvData.
**
** Returns:         Success if OK
**
*******************************************************************************/
tLSC_STATUS Write_Response_To_OutFile(Lsc_ImageInfo_t* image_info,
                                      uint8_t* RecvData, int32_t recvlen,
                                      Ls_TagType tType);

/*******************************************************************************
**
** Function:        Check_Certificate_Tag
**
** Description:     Check certificate Tag presence in script
**                  by 7F21 .
**
** Returns:         Success if Tag found
**
*******************************************************************************/
tLSC_STATUS Check_Certificate_Tag(uint8_t* read_buf, uint16_t* offset1);

/*******************************************************************************
**
** Function:        Check_SerialNo_Tag
**
** Description:     Check Serial number Tag presence in script
**                  by 0x93 .
**
** Returns:         Success if Tag found
**
*******************************************************************************/
tLSC_STATUS Check_SerialNo_Tag(uint8_t* read_buf, uint16_t* offset1);

/*******************************************************************************
**
** Function:        Check_LSRootID_Tag
**
** Description:     Check LS root ID tag presence in script and compare with
**                  select response root ID value.
**
** Returns:         Success if Tag found
**
*******************************************************************************/
tLSC_STATUS Check_LSRootID_Tag(uint8_t* read_buf, uint16_t* offset1);

/*******************************************************************************
**
** Function:        Check_CertHoldID_Tag
**
** Description:     Check certificate holder ID tag presence in script.
**
** Returns:         Success if Tag found
**
*******************************************************************************/
tLSC_STATUS Check_CertHoldID_Tag(uint8_t* read_buf, uint16_t* offset1);

/*******************************************************************************
**
** Function:        Check_Date_Tag
**
** Description:     Check date tags presence in script.
**
** Returns:         Success if Tag found
**
*******************************************************************************/
tLSC_STATUS Check_Date_Tag(uint8_t* read_buf, uint16_t* offset1);

/*******************************************************************************
**
** Function:        Check_45_Tag
**
** Description:     Check 45 tags presence in script and compare the value
**                  with select response tag 45 value
**
** Returns:         Success if Tag found
**
*******************************************************************************/
tLSC_STATUS Check_45_Tag(uint8_t* read_buf, uint16_t* offset1,
                         uint8_t* tag45Len);

/*******************************************************************************
**
** Function:        Certificate_Verification
**
** Description:     Perform the certificate verification by forwarding it to
**                  LS applet.
**
** Returns:         Success if certificate is verified
**
*******************************************************************************/
tLSC_STATUS Certificate_Verification(Lsc_ImageInfo_t* Os_info,
                                     Lsc_TranscieveInfo_t* pTranscv_Info,
                                     uint8_t* read_buf, uint16_t* offset1,
                                     uint8_t* tag45Len);

/*******************************************************************************
**
** Function:        Check_Complete_7F21_Tag
**
** Description:     Traverses the 7F21 tag for verification of each sub tag with
**                  in the 7F21 tag.
**
** Returns:         Success if all tags are verified
**
*******************************************************************************/
tLSC_STATUS Check_Complete_7F21_Tag(Lsc_ImageInfo_t* Os_info,
                                    Lsc_TranscieveInfo_t* pTranscv_Info,
                                    uint8_t* read_buf, uint16_t* offset);

/*******************************************************************************
**
** Function:        LSC_UpdateExeStatus
**
** Description:     Updates LSC status to a file
**
** Returns:         true if success else false
**
*******************************************************************************/
bool LSC_UpdateExeStatus(uint16_t status);

/*******************************************************************************
**
** Function:        Get_LsStatus
**
** Description:     Interface to fetch Loader service client status to JNI,
*Services
**
** Returns:         SUCCESS/FAILURE
**
*******************************************************************************/
tLSC_STATUS Get_LsStatus(uint8_t* pVersion);

/*******************************************************************************
**
** Function:        LSC_SendtoEse
**
** Description:     It is used to send the packet to p61
**
** Returns:         Success if ok.
**
*******************************************************************************/
tLSC_STATUS LSC_SendtoEse(Lsc_ImageInfo_t* Os_info, tLSC_STATUS status,
                          Lsc_TranscieveInfo_t* pTranscv_Info);

/*******************************************************************************
**
** Function:        LSC_SendtoLsc
**
** Description:     It is used to forward the packet to Lsc
**
** Returns:         Success if ok.
**
*******************************************************************************/
tLSC_STATUS LSC_SendtoLsc(Lsc_ImageInfo_t* Os_info, tLSC_STATUS status,
                          Lsc_TranscieveInfo_t* pTranscv_Info,
                          Ls_TagType tType);

/*******************************************************************************
**
** Function:        LSC_CloseChannel
**
** Description:     Closes the previously opened logical channel
**
** Returns:         Success if ok.
**
*******************************************************************************/
tLSC_STATUS LSC_CloseChannel(Lsc_ImageInfo_t* Os_info, tLSC_STATUS status,
                             Lsc_TranscieveInfo_t* pTranscv_Info);

/*******************************************************************************
**
** Function:        LSC_ProcessResp
**
** Description:     Process the response packet received from Lsc
**
** Returns:         Success if ok.
**
*******************************************************************************/
tLSC_STATUS LSC_ProcessResp(Lsc_ImageInfo_t* image_info, int32_t recvlen,
                            Lsc_TranscieveInfo_t* trans_info, Ls_TagType tType);

/*******************************************************************************
**
** Function:        LSC_Check_KeyIdentifier
**
** Description:     Checks and validates certificate
**
** Returns:         Success if ok.
**
*******************************************************************************/
tLSC_STATUS LSC_Check_KeyIdentifier(Lsc_ImageInfo_t* Os_info,
                                    tLSC_STATUS status,
                                    Lsc_TranscieveInfo_t* pTranscv_Info,
                                    uint8_t* temp_buf, tLSC_STATUS flag,
                                    int32_t wNewLen);

/*******************************************************************************
**
** Function:        LSC_ReadScript
**
** Description:     Reads the current line if the script
**
** Returns:         Success if ok.
**
*******************************************************************************/
tLSC_STATUS LSC_ReadScript(Lsc_ImageInfo_t* Os_info, uint8_t* read_buf);

/*******************************************************************************
**
** Function:        Process_EseResponse
**
** Description:     It is used to process the received response packet from ESE
**
** Returns:         Success if ok.
**
*******************************************************************************/
tLSC_STATUS Process_EseResponse(Lsc_TranscieveInfo_t* pTranscv_Info,
                                int32_t recv_len, Lsc_ImageInfo_t* Os_info);

/*******************************************************************************
**
** Function:        Process_SelectRsp
**
** Description:     It is used to process the received response for SELECT LSC
*cmd
**
** Returns:         Success if ok.
**
*******************************************************************************/
tLSC_STATUS Process_SelectRsp(uint8_t* Recv_data, int32_t Recv_len);

/*******************************************************************************
**
** Function:        Numof_lengthbytes
**
** Description:     Checks the number of length bytes and assigns
**                  length value to wLen.
**
** Returns:         Number of Length bytes
**
*******************************************************************************/
uint8_t Numof_lengthbytes(uint8_t* read_buf, int32_t* wLen);

#ifdef JCOP3_WR
tLSC_STATUS Send_Backall_Loadcmds(Lsc_ImageInfo_t* Os_info, tLSC_STATUS status,
                                  Lsc_TranscieveInfo_t* pTranscv_Info);

tLSC_STATUS Bufferize_load_cmds(Lsc_ImageInfo_t* Os_info, tLSC_STATUS status,
                                Lsc_TranscieveInfo_t* pTranscv_Info);
#endif

inline int FSCANF_BYTE(FILE* stream, const char* format, void* pVal) {
  int Result = 0;

  if ((NULL != stream) && (NULL != format) && (NULL != pVal)) {
    unsigned int dwVal;
    unsigned char* pTmp = (unsigned char*)pVal;
    Result = fscanf(stream, format, &dwVal);

    (*pTmp) = (unsigned char)(dwVal & 0x000000FF);
  }
  return Result;
}

#endif /*LSC_H*/
