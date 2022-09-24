#include <stdio.h>
#include <stdlib.h>
//#include <combaseapi.h>
//#include <initguid.h>
#include <Mmdeviceapi.h>
#include <endpointvolume.h>
#include <windows.h>
#include "resource.h"

BOOL ChangeVolume(float nVolume)
{
    HRESULT hr = NULL;
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    if(FAILED(hr))
        return FALSE;

    IMMDevice *defaultDevice = NULL;
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    if(FAILED(hr))
        return FALSE;

    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
        CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    if(FAILED(hr))
        return FALSE;

    hr = endpointVolume->SetMasterVolumeLevelScalar(nVolume, NULL);
    endpointVolume->Release();

    return SUCCEEDED(hr);
}

int main()
{
    CoInitialize(NULL);
    ChangeVolume(0.5);
    CoUninitialize();
    PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE);
    return 0;
}
