#ifndef SOCVERIFICATION_H
#define SOCVERIFICATION_H
typedef struct
{
    int detectVersion;//���汾�Ÿ���
    int detectUseUp;//��⵽��
    int detectMachineCodeChange;//����������
    int detectIpChange;//���IP���
    //�ܼ��һ���࿪ ������࿪ �ǲ����ظ���¼ ���Ҫ��ֹ������࿪�Ϳ���дtrue  
    //��Ϊ������ܿ�¡һ���Ļ������ϵķ�����ⲻ�� ��ʱ����������ܼ�⵽��
    int detectOperationSource;

    int proscribeIP;//���IP�Ƿ񱻷�
    int proscribeMachineCode;//���������Ƿ񱻷�
    int proscribeUser;//����˺��Ƿ񱻷�
}_CS_OptionSwitch, * P_CS_OptionSwitch;

//��ȡ���� �ص�������ȡ���Ƚṹ
typedef struct
{
    
    __int64 DataSize;//���ݴ�С
    __int64 TotalDownloadSize;//�����ش�С
    int PercentageProgress;//�ٷֱȽ���

  
}_CS_GetCallbackProgress, * P_CS_GetCallbackProgress;
//�������ؽ�������Ϣ�ص�����
//void WINAPI DownloadProgress(_CS_GetCallbackProgress ScheduleStructure)
//{
//    printf("�ļ���С��%I64d �����أ�%I64d ����ɣ�%d\n",
//        ScheduleStructure.DataSize,
//        ScheduleStructure.TotalDownloadSize,
//        ScheduleStructure.PercentageProgress);
//}
#ifndef NULL
#define NULL 0
#endif
//���� char**Pbuf ��Ҫ��  _CShield_free(Pbuf); �ͷ�
#ifdef __cplusplus
extern "C" {
#endif

    //��ʼ����֤ 
    // ��ҵ�� ���� �ڴ��ౣ�� ��ֹ��֤�������뱻�򲹶�HOOK����Ϊ �����Ƿ���㻹���ڴ�㶼�г�ǿ��������
    //���� machinecode Ϊ�վ�ʹ��C�ܻ�ȡ�����룬��Ϊ�����Լ���ȡ�����봫�� 
    //���� ProtectionType=1�����ڲ������߳�+���ñ����ڴ������ �߳�ģʽ_begin_VM_push ���� ExecuteTheCode��Ч ProtectionType=0 �������߳� ֻʹ�� ���ñ����ڴ������ //��ҵ���ʹ�ù���
      //host ������дIP Ҳ��д����������������https://www.baidu.com/ ��д www.baidu.com Ҫȥͷȥβ
      bool _Verificationbegins(const char* host, short hostshort, const char* _project, const char* versionNumber, const char* machinecode=NULL, int ProtectionType=0);
    //������
      bool _CheckForUpdates(char* buf);
    //��̨�����ļ�,����1 Ҫд�����ļ�·�� ����2 �ص����� ԭ��void WINAPI DownloadProgress(_CS_GetCallbackProgress ScheduleStructure); ��;�����ļ�ʱ�������ؽ�����
      bool _BackgroundUpdateFile(char* path,void * _cs_function/*=NULL*/);
    //��ѯ
      void _Inquire(const char* _user, char* buf/*=NULL*/);
      //�˺������¼ģʽ ����1 �˺ţ�����2 ���룬����3 ����˵��������4 ���ػƽ�㣬����5 ʣ��ʱ�䡢������������6 ������ 1ʱ�� 2��������2023.6.29 �˺�Ϊ��""�������� ������뿪�����ÿ����ڹ��������Ϊ0��
      bool _login(const char* _user, const char* _password, char* buf = NULL, __int64* GoldenPoint = NULL, __int64* RemainingTime = NULL, int* Cardtype = NULL, char* TypeChinese = NULL);
      //���ܵ�¼ģʽ ����1 ���ܣ�����2 ����˵��������3 ���ػƽ�㣬����4 ʣ��ʱ�䡢������������5 ������ 1ʱ�� 2������ ��2023.6.29 �˺�Ϊ��""�������� ������뿪�����ÿ����ڹ��������Ϊ0��
      bool _CardLogin(const char* _Card, char* buf = NULL, __int64* GoldenPoint = NULL, __int64* RemainingTime = NULL, int* Cardtype = NULL, char* TypeChinese = NULL);
      //���ܵ�¼ģʽ+�Զ���� ����1 ���ܣ�����2 ����˵��������3 ���ػƽ�㣬����4 ʣ��ʱ�䡢������������5 ������ 1ʱ�� 2������ ��2023.6.29 �˺�Ϊ��""�������� ������뿪�����ÿ����ڹ��������Ϊ0��
      bool _CardLogin2(const char* _Card, char* buf = NULL, __int64* GoldenPoint = NULL, __int64* RemainingTime = NULL, int* Cardtype = NULL, char* TypeChinese = NULL);
 
    //�˺�������ģʽ
      void _Untie(const char* _user, const char* _password, char* buf/*=NULL*/);

    //���ܽ��ģʽ
      void _CardUntie(const char* _Card, char* buf/*=NULL*/);
      //�������� �ڹ���� �鿴�û� ����1 �˺ţ�����2 ���� ���ܵ�¼��д�� ""  �˺�����ΪNULL�Ǿ�ʹ�õ�¼ʱ���˺����� �������⣺�������û����������Ч�� ��Ҫ����ǿ�������� ʹ�ñ�����Ҫ��ֹͣ���������ٵ���
      bool _NormalOffline(const char* _user = NULL, const char* _password = NULL, char* buf = NULL);
      //��֤�������Ϸ��� �����ȵ�¼���ٵ��� key �ڹ����->������Ŀ->�Ҽ���Ŀ ��Ŀ�����˵�->��ȡ��ĿУ��ֵ ���ֻ���ÿ������˺Ż�ȡ ������������Ϸ��� �Լ�Ҳ�ÿ����Ƽ���д �����Ӷ�һ�� 
      //type ==0 �쳣ֱ�����ڲ����� type ==1 ����ֵ �� ���� �� �쳣 ����˵�� ����1 ���� У��ֵ ����2 ���� ����3 ���� ����4 ���� ����˵�� �������� 
      bool _VerifyTheValidityOfTheServer(char* key, int keylen, int type, char* buf);
      //�����Ƽ���
      bool _CloudComputing_Customization(char* key, int keylen, char** Prkey, int* Rkeylen, char* buf);

      
    //ע��
      bool _registered(const char* _serialnumber, const char* _user, const char* _password, const char* _SecurityCode, const char* _Referrer, char* buf/*=NULL*/);
    //��ֵ
      bool _Recharge(const char* _serialnumber, const char* _user, char* buf/*=NULL*/);
    //�޸�����
      void _changePassword(const char* _user, const char* _NewPassword, const char* _SecurityCode, char* buf/*=NULL*/);
      //�������� 2023.6.29 ���ù��ܿ��Ե������м�����ж����ù��ܵĺϷ��Ժ��Ƿ�������û����ý���
      __int64 _FunctionalTrial(char* buf);
    // ����֤�ɹ���Ĺ�������Լ��ϱ���⣬�������������¼�ľͻ�ֱ�ӽ�������
      void _CshieldVM();
      //�����Ѿ������� _CshieldVM(); ������Ϊ ��ͨ����� ֱ�ӽ������� _CshieldVM2Ҳ��� _CshieldVM�Ƿ�������
      void _CshieldVM2();
    //�Զ��庯��  ���� _cs_function �ǻص����� ԭ��void WINAPI DownloadProgress(_CS_GetCallbackProgress ScheduleStructure); ��;�����ļ�ʱ�������ؽ�����
      __int64 _CustomFunctionSendData(const char* _user, const char* _password,
          const char* Function, const char* Parameters, const char* data, size_t datalen, char** retbuf/*=NULL*/, void* _cs_function/*=NULL*/);
      //�Զ��庯�� ͨ�ż���  ���� _cs_function �ǻص����� ԭ��void WINAPI DownloadProgress(_CS_GetCallbackProgress ScheduleStructure); ��;�����ļ�ʱ�������ؽ�����
      __int64 _CustomFunctionSendDataEncrypt(const char* _user, const char* _password,
          const char* Function, const char* Parameters, const char* data, size_t datalen, char** retbuf/*=NULL*/, void* _cs_function/*=NULL*/);
      
      //�������û���������
      void _SetMachinecode(bool cpuID, bool HardDrive, bool HardwareID, bool biosID, bool MACAddress);
    //�Զ���ȡ������
      void _GetMachinecode(char* data, size_t datalen, bool cpuID, bool HardDrive, bool HardwareID, bool biosID, bool MACAddress);
  
      /* �Զ����� ���  ����ֵ 0 �쳣 1 ���� 2����ʧ��
       * ����1 ������Ϣ ����2 ��0 ��⵽�쳣������ ���ش�����Ϣ
       * ����2 ���� 0 ��⵽�쳣������Ϣ 1 ����쳣ֱ�ӽ���
       * detectOperationSource �ܼ��һ���࿪ ������࿪ �ǲ����ظ���¼ ���Ҫ��ֹ������࿪�Ϳ���дtrue  ��Ϊ������ܿ�¡һ���Ļ������ϵķ�����ⲻ�� ��ʱ����������ܼ�⵽��*/
       
      int _CustomDetectionEx(char* buf, int type, P_CS_OptionSwitch OptionSwitch);

      /* C�ܼ��ѡ��   ���� 1 ���� 0 �쳣 2����ʧ�� ���ѡ�� �ڹ��������
       * ����1 ������Ϣ ����2 ��0 ��⵽�쳣������ ���ش�����Ϣ
       * ����2 ���� 0 ��⵽�쳣������Ϣ 1 ����쳣ֱ�ӽ���*/
      int _CShieldDetectionOption(char* buf, int type);

      /* ����������֤ ��� ���ѡ�� �ڹ��������
       * ���� Ƶ�� 100��ŵ���1�� ������
       * ������̲߳�Ҫ��ε���  */
      void  _StartHeartbeatVerification(int frequency);
      //����תʱ��(54231654,buf,0) ���ظ�ʽ 627��16Сʱ20����54�� type==1 ���ظ�ʽ ����ʱ��+ʣ��ʱ�� 2023��7��2��15��39��33��
      void _CSconversion_time_fun(__int64 input_seconds, char* buf, int type);
      //��ѯ����ʱ�� ����1 ���ܡ��˺� Ϊ��"" ��ȡ����ʱ��  ����2ֵ ���ؿ����� 1ʱ�� 2������ 3�ƽ�� ����ֵ=���� ��Ҫ�õ���������ֵ*60
      double  _QueryExpirationTime(const char* _user,int* type); //_user����""���ǻ�ȡ����ʱ�� ���õ�ʱ��Ҳ�����������
      //��ȡ�û�ʣ������ ����1 ���� ������ 1ʱ�� 2������ ���õ�ʱ��Ҳ����������� ��¼���ٵ���
      __int64 _GetNumberOfSecondsLeft(int* type, char* buf);

      //��ȡ��������
      __int64  _GetOnlinerate();
      //��������߳��Ƿ���������
      void  _StartHeartbeatVerificationVM_1();
      //�ͷ�C��������ڴ�
      void _CShield_free(void* Pbuf);
      //��ȡ��ַ�� �򹫸�֮���
      bool _GetBaseAddressData(const char* _user, const char* _password,//�˺��������������� ����ģʽ����д�� "" �޳�100
          const char* name, //�������� �޳�100
          const char* SearchType,//�������� �޳�100  Ϊ�ա��� ��ȡ����
          char* Content, size_t Contentlen,//��ȡ������ +���ݻ��峤�� �޳�100
          char* retType, size_t retTypelen,//�������� ����ȡдNULL ��ֹ SearchType���ա��� ��֪������ ���������ȡ
          char** PVeryLargeTextData, size_t* PVeryLargeTextDatalen //���ı� ���س��� char* PVeryLargeTextData=NULL; �ٰ� &PVeryLargeTextData ����ȥ �����ǵ��ͷ� _CShield_free(PVeryLargeTextData);
      );
   
      //��ȡ��ַ�� �򹫸�֮���
      bool _GetBaseAddressData_Encrypt(const char* _user, const char* _password,//�˺��������������� ����ģʽ����д�� "" �޳�100
          const char* name, //�������� �޳�100
          const char* SearchType,//�������� �޳�100  Ϊ�ա��� ��ȡ����
          char* Content, size_t Contentlen,//��ȡ������ +���ݻ��峤�� �޳�100
          char* retType, size_t retTypelen,//�������� ����ȡдNULL ��ֹ SearchType���ա��� ��֪������ ���������ȡ
          char** PVeryLargeTextData, size_t* PVeryLargeTextDatalen //���ı� ���س��� char* PVeryLargeTextData=NULL; �ٰ� &PVeryLargeTextData ����ȥ �����ǵ��ͷ� _CShield_free(PVeryLargeTextData);
      );

      //��ȡ���������� ���� Pbuf �ǵ��ͷ� _CShield_free(Pbuf); ��������Ϸ��ص�����һ�� ����Ϊ�˷��㲻��ȡ������ VeryLargeTextData
     size_t _GetAllTableData(const char* _user, const char* _password,//�˺��������������� ����ģʽ����д�� "" �޳�100
         const char* type, const char* DisplayType, char** Pbuf/*=NULL*/, size_t* VeryLargeTextDatalen/*=NULL*/);//���� û��д�� ""

           //��ȡ���������� ����ͨ�� ���� Pbuf �ǵ� _CShield_free(Pbuf);�ͷ� ��������Ϸ��ص�����һ�� ����Ϊ�˷��㲻��ȡ������ VeryLargeTextData
     size_t _GetAllTableData_Encrypt(const char* _user, const char* _password,//�˺��������������� ����ģʽ����д�� "" �޳�100
         const char* type, const char* DisplayType, char** Pbuf/*=NULL*/, size_t* VeryLargeTextDatalen/*=NULL*/);//���� û��д�� ""

     //��ȡ�����б� ����ֵ ���ع����б���� ����1 ��ȡ���� ������2 �ָ��������3���صĹ����б�  ����4 ���س��� ���� Pbuf �ǵ� _CShield_free(Pbuf);�ͷ� �����б�=������ ����2 �ָ�� ���� ����2 �ָ�� ���ƣ� ��ȡ����==1 ���� _GetAnnouncement ��ر����� ��ȡ����==2 ���� _GetAnnouncementData ��ر����� 
     int _GetListOfAnnouncements(const char* type, const char* Separator, char** Pbuf, size_t* rlength);

      //���û�ַ�� �򹫸�֮�������  �����������һ�� ���ƴ���ֱ�Ӹ������� �����ڻ������µ��������� 
      bool _SetBaseAddressData(
          const char* _user, const char* _password,  //�˺������ǹ���˵� ����һ���и��±�Ȩ�� �������ɿ���Ȩ�޿��Թر� �����Զ��庯�� ������
          const char* name, const char* type, const char* Content,  const char* EnableTime,
          const char* VeryLargeTextData,  size_t VeryLargeTextDatalen);//���ı� ֧�ֶ����ƴ洢 ����

      //�������ñ����� 
      bool _SetBaseAddressDataInBatches(const char* _user, const char* _password, //�˺������ǹ���˵� ����һ���и��±�Ȩ�� �������ɿ���Ȩ�޿��Թر� �����Զ��庯�� ������
          const char* type,
          const char* EnableTime, //ʱ�� 
          const char* senddata,//���ݴ洢��ʽ senddata= {name+ '\0' + Content + '\0'+ name+ '\0' + Content + '\0'+ name+ '\0' + Content+'\0'} �Դ����� ����д��ѭ��
          size_t senddatalen,//senddatalen=senddata End- senddata
          char** Pbuf/*=NULL*/, size_t* buflen/*=NULL*/);   // ��������ָ�룬�������ݳ��� ����ǵ��ͷ� _CShield_free(Pbuf); 
      //�Ƴ�����
      bool _RemoveTableData(const char* _user, const char* _password, const char* SearchType, const char* VersionType, const char* szdata, char* buf/*=NULL*/);//�˺������ǹ���˵�
     
       //��ֵ�ƽ�� ����ֵ �ƽ�㣬����1 ���ܣ�����2 �˺ţ�����3 ����˵�� 
      bool _RechargePointCard(const char* _serialnumber, const char* _user, char* buf/*=NULL*/);
      //��ȡ �ƽ�� ����ֵ �ƽ�㣬����1 �˺ţ�����2 ���룬����3 ����˵�� 
      __int64 _GetGoldenPoints(const char* _user, const char* _password, char* buf/*=NULL*/);
      //���� �ƽ��  ����ֵ �ƽ�㣬����1 �˺ţ�����2 ���룬����3 ��ֵ�� ����4 ����˵�� 
      __int64 _AddGoldenPoints(const char* _user, const char* _password, const char* Value, char* buf/*=NULL*/);
      //���� �ƽ�� ����ֵ �ƽ�㣬����1 �˺ţ�����2 ���룬����3 ��ֵ�� ����4 ����˵��
      __int64 _SubGoldenPoints(const char* _user, const char* _password, const char* Value, char* buf/*=NULL*/);
      //QQ�� ����ֵ �ɹ���ʧ�ܣ�����1 �˺ţ�����2 ���룬����3 ��ȫ�룬����4 QQ�ţ�����5 ����˵������ע������ģʽ�Ĳ��� 2 3д�ա��� ��������ؼ���¼QQ Ȼ���ȡCookies ��������Ի�ȡQQ�� ��QQ�Ž������� �������QQ����֤
      bool _QQBind(char* _user, const char* _password, const char* _SecurityCode, const char* QQ, char* buf/*=NULL*/);
      //QQ��� ����ֵ �ɹ���ʧ�ܣ�����1 �˺ţ�����2 ���룬����3 ��ȫ�룬����4 QQ�ţ�����5 ����˵������ע������ģʽ�Ĳ��� 2 3д�ա��� ��������ؼ���¼QQ Ȼ���ȡCookies ��������Ի�ȡQQ�� ��QQ�Ž������� �������QQ����֤
      bool _QQUnbind(char* _user, const char* _password, const char* _SecurityCode, const char* QQ, char* buf/*=NULL*/);
      //QQ��¼+�Զ���� ����ֵ �ɹ���ʧ�� ����1 QQ�ţ�����2 ����˵������ע����������ؼ���¼QQ Ȼ���ȡCookies ��������Ի�ȡQQ�Ŵ�QQ�Ž������� �������QQ����֤
      bool _QQLogin(const char* QQ, char* buf=NULL, __int64* GoldenPoint = NULL, __int64* RemainingTime = NULL, int* Cardtype = NULL, char* TypeChinese=NULL);
      //QQ��ֵ ����ֵ �ɹ���ʧ�� ����1 ���ܣ�����2 QQ�ţ�����3 ����˵����
      bool _QQRecharge(const char* _Card, const char* QQ, char* buf/*=NULL*/);
      //���ù��� ����ֵ �ɹ���ʧ�ܣ�����1 �˺ţ�����2 ���룬 ����3 ���ƣ�����4 ���ݣ�����5 ���ݳ��ȡ���ע������ ֧�ֶ����ƴ洢 ���Դ� ����ı���DLL��ͼƬ ��
      bool  _SetAnnouncement(char* _user, const char* _password, const char* name, char* buf, size_t length);
      //��ȡ���� ����ֵ �ɹ���ʧ�ܣ�����1 ���ƣ�����2 ��������ָ�룬����3 �������ݳ���  ��ע������ǵ��ͷ� _CShield_free(Pbuf); ����2
      bool _GetAnnouncement(const char* name, char** Pbuf, size_t* VeryLargeTextDatalen);
      //���ù������� ����ֵ �ɹ���ʧ�ܣ�����1 �˺ţ�����2 ���룬 ����3 ���ƣ�����4 MD5������5 ���ݣ�����6 ���ݳ��ȡ���ע������ ֧�ֶ����ƴ洢 ���Դ� ����ı���DLL��ͼƬ ��
      bool _SetAnnouncementData(char* _user, const char* _password, const char* name, const char* md5, char* buf, size_t length);
      //��ȡ�������� ����ֵ �ɹ���ʧ�ܣ�����1 ���ƣ�����2 ��������ָ�룬����3 �������ݳ��� ����4 ����ԭMD5  ����5 ���ؽ��ȵĻص�����  ��ע������ǵ��ͷ� _CShield_free(Pbuf); ����2  ���� _cs_function �ǻص����� ԭ��void WINAPI DownloadProgress(_CS_GetCallbackProgress ScheduleStructure); ��;�����ļ�ʱ�������ؽ�����
      bool _GetAnnouncementData(const char* name, char** Pbuf, size_t* VeryLargeTextDatalen, char* MD5/*=NULL*/, void* _cs_function/*=NULL*/);
      //���ù������� ͨ�ż���
      bool _SetAnnouncementData_Encrypt(char* _user, const char* _password, const char* name, const char* md5, char* buf, size_t length);
      //��ȡ�������� ͨ�ż���
      bool _GetAnnouncementData_Encrypt(const char* name, char** Pbuf, size_t* VeryLargeTextDatalen, char* MD5, void* _cs_function);
      //IP����������ɾ�� type==3 ɾ��IP type==4 ɾ�������� type==5 ����IP type==6 ���ڻ����� type==7 ���IP������ type==8 ��ӻ����������  CustomData=IP���������� Ϊ��"" ��C�ܻ�ȡ �Ƽ�д�� ""
      bool _AddAndDeleteIPOrMachineCode(const char* _user, const char* _password, //�˺������ǹ���˵� ����һ���з�IP�������Ȩ�� �������ɿ���Ȩ�޿��Թر� �����Զ��庯�� ������
          const char* type, const char* CustomData, char* buf);
      //������ڲ����˺ź�IP ����1 ��������,����2 ˵��ԭ��,����3 ����˵�� (�������� type== "0" ReasonText="ϵͳ���"���������� type=="1" ˵��ԭ�� ����Ч��)
      bool _BlockingIsOperatingTheAccountAndIP(const char* type, const char* ReasonText, char* buf);
      //�û����� �˺ţ����룬��ϵ��ʽ�����ݣ�����˵��
      bool _UserMessage(const char* _user, const char* _password, const char* name, const char* Data, char* buf);
      //ģ���������� �˺ţ����룬��ʼʱ��2019-04-02 17:37:49������ʱ��2100-04-10 12:49:49����ϵ��ʽ���������� 0 �û� 1 ��ϵ��ʽ ��¼IP��ģ������ 0 ȫ��ƥ�� 1 ģ��ƥ�䣬�ӵڼ�����ʼ��ȡ����ȡ����������ָ�룬���س��ȣ������������б�ͷ���ƣ��б�ͷ���峤��������ͷ����2������ͷ���峤��
//����ֵ ������
//Pbuf ����Ҫ��if(Pbuf)_CShield_free(Pbuf);  �ͷ�
      //size_t VeryLargeTextDatalen = 0;
      //size_t TotalNumber = 0;
      //char ListNameArray[1000] = { 0 };
      //char ListNameArray2[1000] = { 0 };
      //INT64  number = _FuzzySearchForMessages("����", "", "2019-04-02 17:37:49", "2100-04-10 12:49:49", "1257210463", "0", "0", "0", "1000",
      //    &Pbuf, &VeryLargeTextDatalen, &TotalNumber, &ListNameArray, sizeof(ListNameArray), &ListNameArray2, sizeof(ListNameArray2));
      //if (Pbuf)
      //{
      //    int x = 0;
      //    //printf("%s\n", ListNameArray);
      //    //printf("%s\n", ListNameArray2);
      //    char* p, * next = ListNameArray;
      //    char str[1000] = { 0 };
      //    while (true)
      //    {
      //        p = strtok_s(next, "|", &next);
      //        if (!p)break;
      //        p = strtok_s(p, "#", &str);
      //        if (!p)break;
      //        printf("%s ", p);

      //    }
      //    printf("\n");
      //    next = ListNameArray2;
      //    while (true)
      //    {
      //        p = strtok_s(next, "|", &next);
      //        if (!p)break;
      //        printf("%s ", p);
      //        x++;
      //    }

      //    char* PA = Pbuf;
      //    for (size_t i = 0, t = 1; i < number * x; i++, t++)
      //    {
      //        printf("[%d]%s ", t, PA);
      //        PA += strlen(PA);
      //        PA++;
      //        if (t == x)
      //        {
      //            t = 0;
      //            printf("\n");
      //        }
      //    }
      //    _CShield_free(Pbuf);
      //}

      __int64  _FuzzySearchForMessages(const char* _user, const char* _password,
          const char* szTime1, const char* szTime2, const char* name,
          const char* SearchType, const char* FuzzySearch,
          const char* StartingNumber, const char* GetTheNumber,
          char** Pbuf, size_t* VeryLargeTextDatalen,
          size_t* TotalNumber,
          char* ListNameArray, size_t ListNameArraylen,
          char* ListNameArray2, size_t ListNameArraylen2);
      
      //������� ������˺ţ���������룬�û���ID����ϵ��ʽ������ 0 ��ͨ�� 1 ͨ�� 2 �ȴ���� 3 ɾ�����ظ�������˵��
      bool _UserMessageAudit(const char* _user, const char* _password, const char* accountnumber,
          const char* ID, const char* NAME, const char* type, const char* szReply, char* buf);

      //��ȡVMP����Ȩ ����1 ������� ����2 ������ ����3 �����볤�� ����4 ������Ȩ�� ����5 ������Ȩ�볤�� ����6 ����˵�� ���ó���� ����˵�� ע�⣺Ҫ��¼��ſɵ��� ����ǵ��ͷ� _CShield_free(Pbuf); ����2 
      bool _GetVMPAuthorization(const char* SoftwareName, char* pHardwareID, int HardwareIDLength, char** Pbuf, int* rlength, char* buf);

      //��ȡ����ע ����1�˺� ����2 ���� ����ģʽ ����д�� ""
      bool _GetCardRemarks(const char* _user, const char* _password, char* buf);
      //΢�Ŷ���ȡ�� ����1 ������  ����2 ���صĿ� ȡ�����Ŀ��� ����3 ���س���   ���� Pbuf �ǵ� _CShield_free(Pbuf);�ͷ�
      bool _GetWechatOrderCard(const char* OrderNumber, char** Pbuf, size_t* rlength);
      //��ȡ΢�Ŷ�����ֵ���� ����1 ������  ����2 Ҫ��ֵ�Ĵ����˺� ����3 ����˵��
      bool _GetWechatOrderRechargeAgent(const char* OrderNumber, const char* Agent, char* buf);
      //�ж�΢���տ�����Ƿ������� ����ֵ true ���� false ��ֹͣ���� ����1 ����˵��
      bool _IsWechatWorkingProperly(char* buf);
      /****************************** �ڴ������ ��ҵ�湦�� (��ҵ�����ʹ�ù���) **************************/

      //�ֶ���Ӻ��� ������ ���ƽ� ��HOOK�޸ĺ������� ��������ĺ�����ַ  ������¼��ͨ����غ��� �����ĺ������Թ�����Ҳ�ᱻ���� �Լ����Ե�ʱ��Ӻ��ж�
      //ע�� _Verificationbegins���� ProtectionType=1 ExecuteTheCode ��Ч
      bool  _begin_VM_push(void* FunctionAddr, void*  ExecuteTheCode);//��ҵ���ʹ�ù���
      //�ֶ����ü�� ���Է��ڹ��ܴ��������Ĺ��ܴ������һ��һ����Ӹ��Ӷ� ��������ʵʱ���ü��  �������Ӻ��� �ڵ���C�ܺ�����ʱ��Ҳ����ü��
      bool  _begin_VM_call(int t);//���� t==1��⵽ֱ�������˳�  //��ҵ���ʹ�ù���
       
      //���� �Լ��ֶ���ӱ������� �ڲ�Ҳ �����������Ҫ����
      /****************************** �ڴ������End ****************************/

      /****************************** ͨ�ŷ������ ****************************/
      // �ڲ���Ҫ�����Ѿ����� ͨ�ŷ������ һ���Է�� ����������֤�ɹ�ֻ����֤һ�� ���˸��Ƶ������� ��ѭ��ʹ�� Ҳ����Ч�� 
      /****************************** ͨ�ŷ������End ****************************/


      //MD5
      void _CS_GetMD5(unsigned char* buf, size_t length, unsigned char digest[16]);
      void _CS_GetTextMD5A(unsigned char* buf, size_t length, char digest[33]);
      void _CS_GetTextMD5W(unsigned char* buf, size_t length, wchar_t digest[34]);
      size_t _CS_GetFileMD5A(const char* Path, char digest[33]);
      size_t _CS_GetFileMD5W(const wchar_t* Path, wchar_t digest[34]);
      //��ȡ�ѵ�¼QQ��
      /*char buf[2000] = { 0 };
      size_t number = _CS_GetTheLoggedInQQNumberA(buf);
      char* P = buf;
      for (size_t i = 0; i < number; i++)
      {
          printf("%s\n", P);
          P += strlen(P);
          P++;
      }*/
      size_t _CS_GetTheLoggedInQQNumberA(char* buf, size_t* length/*=NULL*/);
      /*wchar_t wbuf[2000] = { 0 };
      size_t number = _CS_GetTheLoggedInQQNumberA(wbuf);
      wchar_t* P = wbuf;
      for (size_t i = 0; i < number; i++)
      {
          wprintf(L"%ws\n", P);
          P += wcslen(P);
          P++;
      }*/
      size_t  _CS_GetTheLoggedInQQNumberW(wchar_t* buf, size_t* length/*=NULL*/);
      //�ж�QQ�Ƿ��Ѿ���¼
      bool _CS_DetermineWhetherQQIsLoggedIn(const char* QQ);
#ifdef __cplusplus
} /* End Of Extern */
#endif
#endif