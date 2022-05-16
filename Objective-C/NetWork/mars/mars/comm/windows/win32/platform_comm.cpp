/*  Copyright (c) 2013-2015 Tencent. All rights reserved.  */
/**
 * created on : 2012-11-28
 * author : 叶润桂
 */
#include "platform_comm.h"

#include <string>
#include <functional>

#include "xlogger/xlogger.h"
#include "xlogger/loginfo_extract.h"
#include "NetUtil.h"
#include "comm/thread/mutex.h"
#include "comm/thread/lock.h"


using namespace std;

static mars::comm::WifiInfo sg_wifiinfo;
static mars::comm::Mutex sg_wifiinfo_mutex;

namespace mars{
    namespace comm {

        static std::function<bool(std::string&)> g_new_wifi_id_cb;
        static mars::comm::Mutex wifi_id_mutex;

        void SetWiFiIdCallBack(std::function<bool(std::string&)> _cb) {
            mars::comm::ScopedLock lock(wifi_id_mutex);
            g_new_wifi_id_cb = _cb;
        }
        void ResetWiFiIdCallBack() {
            mars::comm::ScopedLock lock(wifi_id_mutex);
            g_new_wifi_id_cb = NULL;
        }

        bool getProxyInfo(int& port, std::string& strProxy, const std::string& _host) {
            xverbose_function();

            return getProxyInfoImpl(port, strProxy, _host);
        }

        bool getCurRadioAccessNetworkInfo(struct RadioAccessNetworkInfo& info) {
            xverbose_function();
            return false;
        }

        int getNetInfo() {
            xverbose_function();

            return isNetworkConnected() ? kWifi : kNoNet;
        }

        unsigned int getSignal(bool isWifi) {
            xverbose_function();
            return (unsigned int)0;
        }

        bool getifaddrs_ipv4_hotspot(std::string& _ifname, std::string& _ip) {
            return false;
        }

        bool isNetworkConnected() {
            return isNetworkConnectedImpl();
        }

        static const char* const SIMULATOR_NET_INFO = "SIMULATOR";
        static const char* const USE_WIRED = "wired";

        bool getCurWifiInfo(WifiInfo& wifiInfo, bool _force_refresh) {
            return false;
        }

        bool getCurSIMInfo(SIMInfo& bsinfo) {
            return false;
        }

        bool getAPNInfo(APNInfo& info) {
            return false;
        }

        int getNetTypeForStatistics() {
            int type = getNetInfo();
            if (mars::comm::kWifi == type) {
                return (int)mars::comm::NetTypeForStatistics::NETTYPE_WIFI;
            }

            return (int)mars::comm::NetTypeForStatistics::NETTYPE_NON;
        }
    }// comm namespace

namespace xlog{

#ifdef NDEBUG
std::function<void (char* _log)> g_console_log_fun = nullptr;
#else
std::function<void (char* _log)> g_console_log_fun = [](char* _log) {
    ::OutputDebugStringA(_log);
};
#endif
void ConsoleLog(const XLoggerInfo* _info, const char* _log)
{
	if (NULL == _info || NULL == _log) return;
	static const char* levelStrings[] = {
		"V",
		"D",  // debug
		"I",  // info
		"W",  // warn
		"E",  // error
		"F"  // fatal
	};
	char strFuncName[128] = { 0 };
	ExtractFunctionName(_info->func_name, strFuncName, sizeof(strFuncName));
	const char* file_name = ExtractFileName(_info->filename);
	char log[16 * 1024] = { 0 };
	snprintf(log, sizeof(log), "[%s][%s][%s, %s, %d][%s\n", levelStrings[_info->level], NULL == _info->tag ? "" : _info->tag, file_name, strFuncName, _info->line, _log);
    if (nullptr != g_console_log_fun) {
        g_console_log_fun(log);
    }
}
}   // namespace xlog
}  // namespace