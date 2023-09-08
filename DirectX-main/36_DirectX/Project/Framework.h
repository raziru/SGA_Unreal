// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once//헤더파일을 한번만 읽어라

#include "__Others/Targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

#include <string>
#include <vector>
#include <map>
#include <functional>

using namespace std;
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

using namespace DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")


#define WIN_WIDTH 1280.0f
#define WIN_HEIGHT 720.0f

#define WIN_CENTER { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f }

#define DEVICE Device::GetInstance()->GetDevice() //리턴 한 변수를 대체한다.
#define DC     Device::GetInstance()->GetDC()

#define KEY_UP(p)    Keyboard::GetInstance()->Up(p)    //p:parameter의 약자 긴 함수를 매크로로 사용한다.
#define KEY_DOWN(p)  Keyboard::GetInstance()->Down(p)  //p:parameter의 약자
#define KEY_PRESS(p) Keyboard::GetInstance()->Press(p) //p:parameter의 약자



#include "Utility/Singleton.h"

#include "Utility/Time.h"
#include "Utility/Keyboard.h"

#include "System/Device.h"

#include "Render/Buffer/VertexLayout.h"
#include "Render/Buffer/VertexBuffer.h"
#include "Render/Buffer/IndexBuffer.h"
#include "Render/Buffer/ConstantBuffer.h"
#include "Render/Buffer/GlobalBuffer.h"


#include "Render/Shader/VertexShader.h"
#include "Render/Shader/PixelShader.h"

#include "System/Environment.h"
#include "Object/Basic/Object.h"
#include "Object/SolarObject/Star.h"
#include "Object/SolarObject/Sun.h"


#include "Scene/Scene.h"
#include "Scene/TutorialScene.h"
#include "Scene/SRTScene.h"
#include "Scene/SolarScene.h"


#include "MainGame.h"


extern HWND hWnd;


