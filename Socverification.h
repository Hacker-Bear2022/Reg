#ifndef SOCVERIFICATION_H
#define SOCVERIFICATION_H
typedef struct
{
    int detectVersion;//检测版本号更新
    int detectUseUp;//检测到期
    int detectMachineCodeChange;//检测机器码变更
    int detectIpChange;//检测IP变更
    //能检测一卡多开 虚拟机多开 是不是重复登录 如果要防止虚拟机多开就可以写true  
    //因为虚拟机能克隆一样的机器码老的方法检测不了 这时候用这个就能检测到了
    int detectOperationSource;

    int proscribeIP;//检测IP是否被封
    int proscribeMachineCode;//检测机器码是否被封
    int proscribeUser;//检测账号是否被封
}_CS_OptionSwitch, * P_CS_OptionSwitch;

//获取数据 回调函数获取进度结构
typedef struct
{
    
    __int64 DataSize;//数据大小
    __int64 TotalDownloadSize;//已下载大小
    int PercentageProgress;//百分比进度

  
}_CS_GetCallbackProgress, * P_CS_GetCallbackProgress;
//所有下载进度条信息回调函数
//void WINAPI DownloadProgress(_CS_GetCallbackProgress ScheduleStructure)
//{
//    printf("文件大小：%I64d 已下载：%I64d 已完成：%d\n",
//        ScheduleStructure.DataSize,
//        ScheduleStructure.TotalDownloadSize,
//        ScheduleStructure.PercentageProgress);
//}
#ifndef NULL
#define NULL 0
#endif
//所有 char**Pbuf 都要用  _CShield_free(Pbuf); 释放
#ifdef __cplusplus
extern "C" {
#endif

    //初始化验证 
    // 企业版 内置 内存汇编保护 防止验证函数代码被打补丁HOOK等行为 不管是封包层还是内存层都有超强防护处理
    //参数 machinecode 为空就使用C盾获取机器码，不为空则自己获取机器码传参 
    //参数 ProtectionType=1就是内部创建线程+内置保护内存防护盾 线程模式_begin_VM_push 参数 ExecuteTheCode无效 ProtectionType=0 不创建线程 只使用 内置保护内存防护盾 //企业版可使用功能
      //host 参数可写IP 也可写域名，比如域名是https://www.baidu.com/ 就写 www.baidu.com 要去头去尾
      bool _Verificationbegins(const char* host, short hostshort, const char* _project, const char* versionNumber, const char* machinecode=NULL, int ProtectionType=0);
    //检查更新
      bool _CheckForUpdates(char* buf);
    //后台更新文件,参数1 要写出的文件路径 参数2 回调函数 原形void WINAPI DownloadProgress(_CS_GetCallbackProgress ScheduleStructure); 用途下载文件时设置下载进度条
      bool _BackgroundUpdateFile(char* path,void * _cs_function/*=NULL*/);
    //查询
      void _Inquire(const char* _user, char* buf/*=NULL*/);
      //账号密码登录模式 参数1 账号，参数2 密码，参数3 返回说明，参数4 返回黄金点，参数5 剩余时间、解绑次数，参数6 卡类型 1时间 2解绑次数（2023.6.29 账号为空""等于试用 如果不想开启试用可以在管理端设置为0）
      bool _login(const char* _user, const char* _password, char* buf = NULL, __int64* GoldenPoint = NULL, __int64* RemainingTime = NULL, int* Cardtype = NULL, char* TypeChinese = NULL);
      //卡密登录模式 参数1 卡密，参数2 返回说明，参数3 返回黄金点，参数4 剩余时间、解绑次数，参数5 卡类型 1时间 2解绑次数 （2023.6.29 账号为空""等于试用 如果不想开启试用可以在管理端设置为0）
      bool _CardLogin(const char* _Card, char* buf = NULL, __int64* GoldenPoint = NULL, __int64* RemainingTime = NULL, int* Cardtype = NULL, char* TypeChinese = NULL);
      //卡密登录模式+自动解绑 参数1 卡密，参数2 返回说明，参数3 返回黄金点，参数4 剩余时间、解绑次数，参数5 卡类型 1时间 2解绑次数 （2023.6.29 账号为空""等于试用 如果不想开启试用可以在管理端设置为0）
      bool _CardLogin2(const char* _Card, char* buf = NULL, __int64* GoldenPoint = NULL, __int64* RemainingTime = NULL, int* Cardtype = NULL, char* TypeChinese = NULL);
 
    //账号密码解绑模式
      void _Untie(const char* _user, const char* _password, char* buf/*=NULL*/);

    //卡密解绑模式
      void _CardUntie(const char* _Card, char* buf/*=NULL*/);
      //正常下线 在管理端 查看用户 参数1 账号，参数2 密码 卡密登录的写空 ""  账号密码为NULL是就使用登录时的账号密码 常见问题：这个功能没有踢人下线效果 不要当成强踢下线用 使用本功能要先停止心跳功能再调用
      bool _NormalOffline(const char* _user = NULL, const char* _password = NULL, char* buf = NULL);
      //验证服务器合法性 必须先登录了再调用 key 在管理端->设置项目->右键项目 项目弹出菜单->获取项目校验值 这个只能用开发者账号获取 这个检测服务器合法性 自己也用可以云计算写 这样加多一层 
      //type ==0 异常直接拉黑并结束 type ==1 返回值 真 正常 假 异常 参数说明 参数1 传入 校验值 参数2 长度 参数3 类型 参数4 传出 返回说明 传出参数 
      bool _VerifyTheValidityOfTheServer(char* key, int keylen, int type, char* buf);
      //定制云计算
      bool _CloudComputing_Customization(char* key, int keylen, char** Prkey, int* Rkeylen, char* buf);

      
    //注册
      bool _registered(const char* _serialnumber, const char* _user, const char* _password, const char* _SecurityCode, const char* _Referrer, char* buf/*=NULL*/);
    //充值
      bool _Recharge(const char* _serialnumber, const char* _user, char* buf/*=NULL*/);
    //修改密码
      void _changePassword(const char* _user, const char* _NewPassword, const char* _SecurityCode, char* buf/*=NULL*/);
      //功能试用 2023.6.29 试用功能可以调用所有检查来判断试用功能的合法性和是否可以试用或试用结束
      __int64 _FunctionalTrial(char* buf);
    // 在验证成功后的功能里可以加上本检测，如果不是正常登录的就会直接结束程序。
      void _CshieldVM();
      //必须已经调用了 _CshieldVM(); 否则视为 不通过检测 直接结束程序。 _CshieldVM2也检测 _CshieldVM是否检测正常
      void _CshieldVM2();
    //自定义函数  参数 _cs_function 是回调函数 原形void WINAPI DownloadProgress(_CS_GetCallbackProgress ScheduleStructure); 用途下载文件时设置下载进度条
      __int64 _CustomFunctionSendData(const char* _user, const char* _password,
          const char* Function, const char* Parameters, const char* data, size_t datalen, char** retbuf/*=NULL*/, void* _cs_function/*=NULL*/);
      //自定义函数 通信加密  参数 _cs_function 是回调函数 原形void WINAPI DownloadProgress(_CS_GetCallbackProgress ScheduleStructure); 用途下载文件时设置下载进度条
      __int64 _CustomFunctionSendDataEncrypt(const char* _user, const char* _password,
          const char* Function, const char* Parameters, const char* data, size_t datalen, char** retbuf/*=NULL*/, void* _cs_function/*=NULL*/);
      
      //设置内置机器码类型
      void _SetMachinecode(bool cpuID, bool HardDrive, bool HardwareID, bool biosID, bool MACAddress);
    //自定获取机器码
      void _GetMachinecode(char* data, size_t datalen, bool cpuID, bool HardDrive, bool HardwareID, bool biosID, bool MACAddress);
  
      /* 自定义检测 检测  返回值 0 异常 1 正常 2连接失败
       * 参数1 返回信息 参数2 传0 检测到异常不崩溃 返回错误信息
       * 参数2 类型 0 检测到异常返回信息 1 检测异常直接结束
       * detectOperationSource 能检测一卡多开 虚拟机多开 是不是重复登录 如果要防止虚拟机多开就可以写true  因为虚拟机能克隆一样的机器码老的方法检测不了 这时候用这个就能检测到了*/
       
      int _CustomDetectionEx(char* buf, int type, P_CS_OptionSwitch OptionSwitch);

      /* C盾检测选项   返回 1 正常 0 异常 2连接失败 检测选项 在管理端设置
       * 参数1 返回信息 参数2 传0 检测到异常不崩溃 返回错误信息
       * 参数2 类型 0 检测到异常返回信息 1 检测异常直接结束*/
      int _CShieldDetectionOption(char* buf, int type);

      /* 启动心跳验证 检测 检测选项 在管理端设置
       * 参数 频率 100大概等于1秒 整数型
       * 这个是线程不要多次调用  */
      void  _StartHeartbeatVerification(int frequency);
      //秒数转时间(54231654,buf,0) 返回格式 627天16小时20分钟54秒 type==1 返回格式 现在时间+剩余时间 2023年7月2日15点39分33秒
      void _CSconversion_time_fun(__int64 input_seconds, char* buf, int type);
      //查询到期时间 参数1 卡密、账号 为空"" 获取试用时间  参数2值 返回卡类型 1时间 2解绑次数 3黄金点 返回值=分钟 想要得到秒数返回值*60
      double  _QueryExpirationTime(const char* _user,int* type); //_user等于""就是获取试用时间 试用的时间也可以在这里查
      //获取用户剩余秒数 参数1 返回 卡类型 1时间 2解绑次数 试用的时间也可以在这里查 登录后再调用
      __int64 _GetNumberOfSecondsLeft(int* type, char* buf);

      //获取在线人数
      __int64  _GetOnlinerate();
      //检测心跳线程是否正常运行
      void  _StartHeartbeatVerificationVM_1();
      //释放C盾申请的内存
      void _CShield_free(void* Pbuf);
      //获取基址表 或公告之类的
      bool _GetBaseAddressData(const char* _user, const char* _password,//账号密码是软件本身的 卡密模式密码写空 "" 限长100
          const char* name, //查找名称 限长100
          const char* SearchType,//搜索类型 限长100  为空“” 获取所有
          char* Content, size_t Contentlen,//获取的内容 +内容缓冲长度 限长100
          char* retType, size_t retTypelen,//返回类型 不获取写NULL 防止 SearchType传空“” 不知道类型 可以在这获取
          char** PVeryLargeTextData, size_t* PVeryLargeTextDatalen //长文本 返回长度 char* PVeryLargeTextData=NULL; 再把 &PVeryLargeTextData 传进去 用完后记得释放 _CShield_free(PVeryLargeTextData);
      );
   
      //获取基址表 或公告之类的
      bool _GetBaseAddressData_Encrypt(const char* _user, const char* _password,//账号密码是软件本身的 卡密模式密码写空 "" 限长100
          const char* name, //查找名称 限长100
          const char* SearchType,//搜索类型 限长100  为空“” 获取所有
          char* Content, size_t Contentlen,//获取的内容 +内容缓冲长度 限长100
          char* retType, size_t retTypelen,//返回类型 不获取写NULL 防止 SearchType传空“” 不知道类型 可以在这获取
          char** PVeryLargeTextData, size_t* PVeryLargeTextDatalen //长文本 返回长度 char* PVeryLargeTextData=NULL; 再把 &PVeryLargeTextData 传进去 用完后记得释放 _CShield_free(PVeryLargeTextData);
      );

      //获取表所有数据 用完 Pbuf 记得释放 _CShield_free(Pbuf); 跟管理端上返回的数据一样 这里为了方便不获取长数据 VeryLargeTextData
     size_t _GetAllTableData(const char* _user, const char* _password,//账号密码是软件本身的 卡密模式密码写空 "" 限长100
         const char* type, const char* DisplayType, char** Pbuf/*=NULL*/, size_t* VeryLargeTextDatalen/*=NULL*/);//类型 没有写空 ""

           //获取表所有数据 加密通信 用完 Pbuf 记得 _CShield_free(Pbuf);释放 跟管理端上返回的数据一样 这里为了方便不获取长数据 VeryLargeTextData
     size_t _GetAllTableData_Encrypt(const char* _user, const char* _password,//账号密码是软件本身的 卡密模式密码写空 "" 限长100
         const char* type, const char* DisplayType, char** Pbuf/*=NULL*/, size_t* VeryLargeTextDatalen/*=NULL*/);//类型 没有写空 ""

     //获取公告列表 返回值 返回公告列表个数 参数1 获取类型 ，参数2 分割符，参数3返回的公告列表  参数4 返回长度 用完 Pbuf 记得 _CShield_free(Pbuf);释放 公告列表=｛名称 参数2 分割符 名称 参数2 分割符 名称｝ 获取类型==1 返回 _GetAnnouncement 相关表数据 获取类型==2 返回 _GetAnnouncementData 相关表数据 
     int _GetListOfAnnouncements(const char* type, const char* Separator, char** Pbuf, size_t* rlength);

      //设置基址表 或公告之类的内容  参数和上面的一样 名称存在直接更新内容 不存在会增加新的名称内容 
      bool _SetBaseAddressData(
          const char* _user, const char* _password,  //账号密码是管理端的 设置一个有更新表权限 其它生成卡密权限可以关闭 或用自定义函数 来操作
          const char* name, const char* type, const char* Content,  const char* EnableTime,
          const char* VeryLargeTextData,  size_t VeryLargeTextDatalen);//长文本 支持二进制存储 长度

      //批量设置表数据 
      bool _SetBaseAddressDataInBatches(const char* _user, const char* _password, //账号密码是管理端的 设置一个有更新表权限 其它生成卡密权限可以关闭 或用自定义函数 来操作
          const char* type,
          const char* EnableTime, //时间 
          const char* senddata,//数据存储方式 senddata= {name+ '\0' + Content + '\0'+ name+ '\0' + Content + '\0'+ name+ '\0' + Content+'\0'} 以此类推 可以写成循环
          size_t senddatalen,//senddatalen=senddata End- senddata
          char** Pbuf/*=NULL*/, size_t* buflen/*=NULL*/);   // 返回数据指针，返回数据长度 用完记得释放 _CShield_free(Pbuf); 
      //移除数据
      bool _RemoveTableData(const char* _user, const char* _password, const char* SearchType, const char* VersionType, const char* szdata, char* buf/*=NULL*/);//账号密码是管理端的
     
       //充值黄金点 返回值 黄金点，参数1 卡密，参数2 账号，参数3 返回说明 
      bool _RechargePointCard(const char* _serialnumber, const char* _user, char* buf/*=NULL*/);
      //获取 黄金点 返回值 黄金点，参数1 账号，参数2 密码，参数3 返回说明 
      __int64 _GetGoldenPoints(const char* _user, const char* _password, char* buf/*=NULL*/);
      //增加 黄金点  返回值 黄金点，参数1 账号，参数2 密码，参数3 数值， 参数4 返回说明 
      __int64 _AddGoldenPoints(const char* _user, const char* _password, const char* Value, char* buf/*=NULL*/);
      //减少 黄金点 返回值 黄金点，参数1 账号，参数2 密码，参数3 数值， 参数4 返回说明
      __int64 _SubGoldenPoints(const char* _user, const char* _password, const char* Value, char* buf/*=NULL*/);
      //QQ绑定 返回值 成功、失败，参数1 账号，参数2 密码，参数3 安全码，参数4 QQ号，参数5 返回说明。备注：卡密模式的参数 2 3写空“” 用浏览器控件登录QQ 然后获取Cookies 在里面可以获取QQ号 传QQ号进来就行 这等于用QQ做验证
      bool _QQBind(char* _user, const char* _password, const char* _SecurityCode, const char* QQ, char* buf/*=NULL*/);
      //QQ解绑 返回值 成功、失败，参数1 账号，参数2 密码，参数3 安全码，参数4 QQ号，参数5 返回说明。备注：卡密模式的参数 2 3写空“” 用浏览器控件登录QQ 然后获取Cookies 在里面可以获取QQ号 传QQ号进来就行 这等于用QQ做验证
      bool _QQUnbind(char* _user, const char* _password, const char* _SecurityCode, const char* QQ, char* buf/*=NULL*/);
      //QQ登录+自动解绑 返回值 成功、失败 参数1 QQ号，参数2 返回说明。备注：用浏览器控件登录QQ 然后获取Cookies 在里面可以获取QQ号传QQ号进来就行 这等于用QQ做验证
      bool _QQLogin(const char* QQ, char* buf=NULL, __int64* GoldenPoint = NULL, __int64* RemainingTime = NULL, int* Cardtype = NULL, char* TypeChinese=NULL);
      //QQ充值 返回值 成功、失败 参数1 卡密，参数2 QQ号，参数3 返回说明。
      bool _QQRecharge(const char* _Card, const char* QQ, char* buf/*=NULL*/);
      //设置公告 返回值 成功、失败，参数1 账号，参数2 密码， 参数3 名称，参数4 数据，参数5 数据长度。备注：数据 支持二进制存储 可以存 广告文本、DLL、图片 等
      bool  _SetAnnouncement(char* _user, const char* _password, const char* name, char* buf, size_t length);
      //获取公告 返回值 成功、失败，参数1 名称，参数2 返回数据指针，参数3 返回数据长度  备注：用完记得释放 _CShield_free(Pbuf); 参数2
      bool _GetAnnouncement(const char* name, char** Pbuf, size_t* VeryLargeTextDatalen);
      //设置公告数据 返回值 成功、失败，参数1 账号，参数2 密码， 参数3 名称，参数4 MD5，参数5 数据，参数6 数据长度。备注：数据 支持二进制存储 可以存 广告文本、DLL、图片 等
      bool _SetAnnouncementData(char* _user, const char* _password, const char* name, const char* md5, char* buf, size_t length);
      //获取公告数据 返回值 成功、失败，参数1 名称，参数2 返回数据指针，参数3 返回数据长度 参数4 返回原MD5  参数5 下载进度的回调函数  备注：用完记得释放 _CShield_free(Pbuf); 参数2  参数 _cs_function 是回调函数 原形void WINAPI DownloadProgress(_CS_GetCallbackProgress ScheduleStructure); 用途下载文件时设置下载进度条
      bool _GetAnnouncementData(const char* name, char** Pbuf, size_t* VeryLargeTextDatalen, char* MD5/*=NULL*/, void* _cs_function/*=NULL*/);
      //设置公告数据 通信加密
      bool _SetAnnouncementData_Encrypt(char* _user, const char* _password, const char* name, const char* md5, char* buf, size_t length);
      //获取公告数据 通信加密
      bool _GetAnnouncementData_Encrypt(const char* name, char** Pbuf, size_t* VeryLargeTextDatalen, char* MD5, void* _cs_function);
      //IP或机器码添加删除 type==3 删除IP type==4 删除机器码 type==5 拉黑IP type==6 拉黑机器码 type==7 添加IP白名单 type==8 添加机器码白名单  CustomData=IP机器码数据 为空"" 由C盾获取 推荐写空 ""
      bool _AddAndDeleteIPOrMachineCode(const char* _user, const char* _password, //账号密码是管理端的 设置一个有封IP封机器码权限 其它生成卡密权限可以关闭 或用自定义函数 来操作
          const char* type, const char* CustomData, char* buf);
      //封禁正在操作账号和IP 参数1 操作类型,参数2 说明原因,参数3 返回说明 (操作类型 type== "0" ReasonText="系统检测"，操作类型 type=="1" 说明原因 才有效果)
      bool _BlockingIsOperatingTheAccountAndIP(const char* type, const char* ReasonText, char* buf);
      //用户留言 账号，密码，联系方式，内容，返回说明
      bool _UserMessage(const char* _user, const char* _password, const char* name, const char* Data, char* buf);
      //模糊搜索留言 账号，密码，开始时间2019-04-02 17:37:49，结束时间2100-04-10 12:49:49，联系方式，搜索类型 0 用户 1 联系方式 登录IP，模糊搜索 0 全字匹配 1 模糊匹配，从第几个开始获取，获取个数，返回指针，返回长度，总留言数，列表头名称，列表头缓冲长数，数据头名称2，数据头缓冲长数
//返回值 留言数
//Pbuf 用完要用if(Pbuf)_CShield_free(Pbuf);  释放
      //size_t VeryLargeTextDatalen = 0;
      //size_t TotalNumber = 0;
      //char ListNameArray[1000] = { 0 };
      //char ListNameArray2[1000] = { 0 };
      //INT64  number = _FuzzySearchForMessages("卡密", "", "2019-04-02 17:37:49", "2100-04-10 12:49:49", "1257210463", "0", "0", "0", "1000",
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
      
      //审核留言 管理端账号，管理端密码，用户，ID，联系方式，类型 0 不通过 1 通过 2 等待审核 3 删除，回复，返回说明
      bool _UserMessageAudit(const char* _user, const char* _password, const char* accountnumber,
          const char* ID, const char* NAME, const char* type, const char* szReply, char* buf);

      //获取VMP云授权 参数1 软件名称 参数2 机器码 参数3 机器码长度 参数4 返回授权码 参数5 返回授权码长度 参数6 返回说明 调用出错会 返回说明 注意：要登录后才可调用 用完记得释放 _CShield_free(Pbuf); 参数2 
      bool _GetVMPAuthorization(const char* SoftwareName, char* pHardwareID, int HardwareIDLength, char** Pbuf, int* rlength, char* buf);

      //获取卡备注 参数1账号 参数2 密码 卡密模式 密码写空 ""
      bool _GetCardRemarks(const char* _user, const char* _password, char* buf);
      //微信订单取卡 参数1 订单号  参数2 返回的卡 取回来的卡密 参数3 返回长度   用完 Pbuf 记得 _CShield_free(Pbuf);释放
      bool _GetWechatOrderCard(const char* OrderNumber, char** Pbuf, size_t* rlength);
      //获取微信订单充值代理 参数1 订单号  参数2 要充值的代理账号 参数3 返回说明
      bool _GetWechatOrderRechargeAgent(const char* OrderNumber, const char* Agent, char* buf);
      //判断微信收款程序是否工作正常 返回值 true 正常 false 已停止工作 参数1 返回说明
      bool _IsWechatWorkingProperly(char* buf);
      /****************************** 内存防护盾 企业版功能 (企业版可以使用功能) **************************/

      //手动添加函数 防护盾 防破解 防HOOK修改函数代码 添加你代码的函数地址  保护登录和通信相关函数 保护的函数调试过程中也会被触发 自己调试的时候加好判断
      //注意 _Verificationbegins参数 ProtectionType=1 ExecuteTheCode 无效
      bool  _begin_VM_push(void* FunctionAddr, void*  ExecuteTheCode);//企业版可使用功能
      //手动调用检测 可以放在功能代码里和你的功能代码绑定在一个一起添加复杂度 本函数可实时调用检测  上面的添加函数 在调用C盾函数的时候也会调用检测
      bool  _begin_VM_call(int t);//参数 t==1检测到直接拉黑退出  //企业版可使用功能
       
      //除了 自己手动添加保护函数 内部也 保护了相关重要函数
      /****************************** 内存防护盾End ****************************/

      /****************************** 通信封包防护 ****************************/
      // 内部重要函数已经做了 通信封包防护 一次性封包 真正做到验证成功只能验证一次 别人复制到这个封包 想循环使用 也是无效的 
      /****************************** 通信封包防护End ****************************/


      //MD5
      void _CS_GetMD5(unsigned char* buf, size_t length, unsigned char digest[16]);
      void _CS_GetTextMD5A(unsigned char* buf, size_t length, char digest[33]);
      void _CS_GetTextMD5W(unsigned char* buf, size_t length, wchar_t digest[34]);
      size_t _CS_GetFileMD5A(const char* Path, char digest[33]);
      size_t _CS_GetFileMD5W(const wchar_t* Path, wchar_t digest[34]);
      //获取已登录QQ号
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
      //判断QQ是否已经登录
      bool _CS_DetermineWhetherQQIsLoggedIn(const char* QQ);
#ifdef __cplusplus
} /* End Of Extern */
#endif
#endif