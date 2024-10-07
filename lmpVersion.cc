#include <napi.h>

#ifdef _WIN32
#include <iostream>
#include <windows.h>
#include <bluetoothapis.h>
#include <bthioctl.h>
#pragma comment(lib, "Bthprops.lib") 
#endif

Napi::Value GetBluetoothLMPVersion(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int lmpVersion = -1;

#ifdef _WIN32
    BLUETOOTH_FIND_RADIO_PARAMS params;
    params.dwSize = sizeof(params);
    HANDLE hRadio;
    HBLUETOOTH_RADIO_FIND hFind = ::BluetoothFindFirstRadio(&params, &hRadio);
    if (hFind) {
        do {
            {
                BTH_LOCAL_RADIO_INFO output;
                DWORD returned;
                if (::DeviceIoControl(hRadio, IOCTL_BTH_GET_LOCAL_INFO, NULL, 0, &output, sizeof(output), &returned, NULL)) {
                    lmpVersion = (unsigned)output.radioInfo.lmpVersion;
                }
            }
            ::CloseHandle(hRadio);
        } while (::BluetoothFindNextRadio(hFind, &hRadio));
        ::BluetoothFindRadioClose(hFind);
    }
#endif

    return Napi::Number::New(env, lmpVersion);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "getBluetoothLMPVersion"), Napi::Function::New(env, GetBluetoothLMPVersion));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)