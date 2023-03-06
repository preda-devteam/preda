#include "user_inputs.h"
#include "../rt/string_type_ops.h"


#if defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
extern void _objc_view_get_size(LPVOID pView, int* w, int *h);
#endif

#if defined(PLATFORM_MAC)
extern void _objc_view_accept_mousemove(LPVOID pView, bool set);
extern bool _objc_pumpevents();
#endif

namespace os
{

namespace _details
{
#if defined(PLATFORM_WIN)
	bool g_MouseSwapButton = GetSystemMetrics(SM_SWAPBUTTON);
#else
#endif
} // namespace _details


bool UserInputState::InitDevices(DWORD devices)
{
#if defined(PLATFORM_WIN)
	if(0 == (UIDEV_MASK_MOBILE & devices))
		return true;
#else
#endif
	return false;
}

bool UserInputState::GetMousePosition(int* xy)	// {x,y}[]
{
#if defined(PLATFORM_WIN)
	return ::GetCursorPos((LPPOINT)xy);
#else
#endif
	return false;
}

DWORD UserInputState::GetPollButtonState(DWORD button_interested)
{
	int ret = 0;
#if defined(PLATFORM_WIN)
	if(button_interested&BUTTON_MOUSE_MASK)
	{
		if(_details::g_MouseSwapButton)
		{
			if((button_interested&BUTTON_MOUSE_LEFT) && ::GetAsyncKeyState(VK_LBUTTON))ret |= BUTTON_MOUSE_LEFT;
			if((button_interested&BUTTON_MOUSE_RIGHT) && ::GetAsyncKeyState(VK_RBUTTON))ret |= BUTTON_MOUSE_RIGHT;
		}
		else
		{
			if((button_interested&BUTTON_MOUSE_LEFT) && ::GetAsyncKeyState(VK_RBUTTON))ret |= BUTTON_MOUSE_LEFT;
			if((button_interested&BUTTON_MOUSE_RIGHT) && ::GetAsyncKeyState(VK_LBUTTON))ret |= BUTTON_MOUSE_RIGHT;
		}
	}
	if(button_interested&BUTTON_KB_MASK)
	{
		if((button_interested&BUTTON_KB_CONTROL) && ::GetAsyncKeyState(VK_CONTROL))ret |= BUTTON_KB_CONTROL;
		if((button_interested&BUTTON_KB_SHIFT) && ::GetAsyncKeyState(VK_SHIFT))ret |= BUTTON_KB_SHIFT;
		if((button_interested&BUTTON_KB_ALT) && ::GetAsyncKeyState(VK_MENU))ret |= BUTTON_KB_ALT;
	}

#else
#endif
	return ret;
}

} // namespac os


namespace os
{

UserInputEventPump::UserInputEventPump()
{
	ASSERT(g_pSingletone == nullptr);
	g_pSingletone = this;

	//_DownCount = 0;
	_pCurrentEvent = nullptr;
	_Timer.LoadCurrentCount();
	_LastViewportWidth = -1;
	_LastViewportHeight = -1;

#if	defined(PLATFORM_WIN)
	_Wnd_Subclassed = NULL;
	_WndProc_Org = NULL;
	_MouseDragKeycode = 0;
#elif defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
	#if defined(PLATFORM_MAC)
	_ViewHeight = 2048;
	#endif
	_bDragging = false;
	#if defined(PLATFORM_MAC)
	_rolloverTrackingRectTag = 0;
	#endif
#else
	ASSERT_STATIC_NOT_IMPLMENTED;
#endif
}

void UserInputEventPump::Term()
{
	if(_Handlers.GetSize())
	{	
		UserInputEvent e;
		e.Type = UIEVT_SYS;
		e.Timestamp = _Timer.TimeLapse();
		e.Device = UIDEV_SYS;
		e.SysCode = SC_UNSUBSCRIBED;
		
		for(UINT i=0;i<_Handlers.GetSize();i++)
			_Handlers[i].pHandler->OnUserInputEvent(e);

		_Handlers.SetSize(0);
	}

#if	defined(PLATFORM_WIN)
	if(_Wnd_Subclassed && _WndProc_Org)
	{
	#ifndef _WIN64
	::SetWindowLongPtr(_Wnd_Subclassed, GWLP_WNDPROC,(LONG)(_WndProc_Org));
	#else
	::SetWindowLongPtr(_Wnd_Subclassed, GWLP_WNDPROC,(LONG_PTR)(_WndProc_Org));
	#endif
	}
#else
#endif
}

void UserInputEventPump::_DispatchEvent(const UserInputEvent& x)
{
	_pCurrentEvent = &x;
	for(UINT i=0;i<_Handlers.GetSize();i++)
	{
		_eventhandler& eh = _Handlers[i];
		if((eh.DeviceMask&x.Device) || x.Device==UIDEV_SYS)
			eh.pHandler->OnUserInputEvent(x);
	}
}

void UserInputEventPump::AddSubscriber(UserInputSubscriber* h, DWORD device_interested)
{
	for(UINT i=0;i<_Handlers.GetSize();i++)
		if(_Handlers[i].pHandler == h)
		{	_Handlers[i].DeviceMask = device_interested;
			return;
		}

	_eventhandler& eh = _Handlers.push_back();
	eh.DeviceMask = device_interested;
	eh.pHandler = h;

	UserInputEvent e;
	e.Type = UIEVT_SYS;
	e.Timestamp = _Timer.TimeLapse();
	e.Device = UIDEV_SYS;
	e.SysCode = SC_SUBSCRIBED;
	h->OnUserInputEvent(e);
}

void UserInputEventPump::RemoveSubscriber(UserInputSubscriber* h)
{
	for(UINT i=0;i<_Handlers.GetSize();i++)
		if(_Handlers[i].pHandler == h)
		{	
			UserInputEvent e;
			e.Type = UIEVT_SYS;
			e.Timestamp = _Timer.TimeLapse();
			e.Device = UIDEV_SYS;
			e.SysCode = SC_UNSUBSCRIBED;
			h->OnUserInputEvent(e);

			_Handlers.erase(i);
			return;
		}
}

void UserInputEventPump::SendEvent(UserInputEvent& e)
{
    e.Timestamp = _Timer.TimeLapse();
    _DispatchEvent(e);
}
    
void UserInputEventPump::SendEvent_Command(DWORD cmdid, LPVOID param)
{
    UserInputEvent e;
    e.Type = UIEVT_COMMAND;
    e.Device = UIEVT_COMMAND;
    e.CmdId = cmdid;
    e.Param = param;
    e.Timestamp = _Timer.TimeLapse();
    _DispatchEvent(e);
}
    
void UserInputEvent::Log() const
{
	LPCSTR names[] = 
	{
		"UIEVT_SYS",
        "UIEVT_COMMAND",        // CmdId,Param
		"UIEVT_KEY_DOWN",		// KeyCode
		"UIEVT_KEY_UP",		// KeyCode
		"UIEVT_MOUSE_DOWN",	// Position", ButtonCode
		"UIEVT_MOUSE_UP",		// Position", ButtonCode
		"UIEVT_MOUSE_MOVE",	// Position
		"UIEVT_MOUSE_DRAGBEGIN",	// Position", ButtonCode
		"UIEVT_MOUSE_DRAG",		// Position", ButtonCode
		"UIEVT_MOUSE_DRAGEND",	// Position", ButtonCode
		"UIEVT_MOUSE_WHEEL",		// Position", Delta
		"UIEVT_VIEWPORT_RESIZE",		// Position", Delta
		"UIEVT_VIEWPORT_REDRAW",		// Position", Delta
	};

	rt::String	str;
	switch(Type)
	{
	case os::UIEVT_KEY_DOWN:
	case os::UIEVT_KEY_UP:
		str = rt::tos::Number((int)KeyCode);
		break;
	case os::UIEVT_MOUSE_DOWN:
	case os::UIEVT_MOUSE_UP:
	case os::UIEVT_MOUSE_MOVE:
	case os::UIEVT_MOUSE_DRAGBEGIN:
	case os::UIEVT_MOUSE_DRAG:
	case os::UIEVT_MOUSE_DRAGEND:
		str = rt::tos::Number((int)ButtonCode) + '|' + (Position.x) + ',' + (Position.y);
		break;
	case os::UIEVT_MOUSE_WHEEL:
		str = rt::tos::Number((int)Delta) + '|' + (Position.x) + ',' + (Position.y);
		break;
	case os::UIEVT_VIEWPORT_RESIZE:
		str = rt::String_Ref() + (Size.width) + ',' + (Size.height);
		break;
	case os::UIEVT_SYS:
		str = rt::tos::Number((int)SysCode);
		break;
    case os::UIEVT_COMMAND:
        str = rt::tos::Number(CmdId) + ',' + rt::tos::Number(Param);
        break;
	}

	_LOG(names[Type]<<':'<<Timestamp<<'\t'<<str);
}

UserInputEventPump*	UserInputEventPump::g_pSingletone = nullptr;

} // namespace os


#if	defined(PLATFORM_WIN)

namespace os
{

bool UserInputEventPump::Init(HWND wnd, DWORD device_interested)
{
	ASSERT(wnd);

	_DeviceInterested = device_interested;
	//if(0 == (UIDEV_MASK_MOBILE & device_interested)){}
	//else return false;

	struct _call
	{	static LRESULT CALLBACK _CommonWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			UserInputEventPump* pump = UserInputEventPump::Get();
			if(pump->_Wnd_Subclassed == hWnd)
			{
				return pump->_WndProc(hWnd,message,wParam,lParam);
			}
			else return DefWindowProc(hWnd,message,wParam,lParam);
//
//#pragma warning(disable:4312)
//			UserInputEventPump* P_WND = (UserInputEventPump*)::GetWindowLongPtr(hWnd,GWLP_USERDATA);
//#pragma warning(default:4312)
//			if(P_WND){ return P_WND->_WndProc(hWnd,message,wParam,lParam); }
			
		}
	};

#pragma warning(disable: 4312) // warning C4312: 'type cast' : conversion from 'LONG' to 'WNDPROC' of greater size
	_WndProc_Org = (WNDPROC)::GetWindowLongPtr(wnd, GWLP_WNDPROC);
	#ifndef _WIN64
	::SetWindowLongPtr(wnd, GWLP_WNDPROC,(LONG)(_call::_CommonWndProc));
	#else
	::SetWindowLongPtr(wnd, GWLP_WNDPROC,(LONG_PTR)(_call::_CommonWndProc));
	#endif
#pragma warning(default:4312)

	_Wnd_Subclassed = wnd;

	{	RECT rc;
		::GetClientRect(wnd, &rc);
		_LastViewportWidth = rc.right - rc.left;
		_LastViewportHeight = rc.bottom - rc.top;

		if(_LastViewportWidth && _LastViewportHeight)
		{
			UserInputEvent	e;
			e.Device = UIDEV_VIEWPORT;
			e.Timestamp = _Timer.TimeLapse();
			e.Type = UIEVT_VIEWPORT_RESIZE;
			e.Size.width = _LastViewportWidth;
			e.Size.height = _LastViewportHeight;
			_DispatchEvent(e);
		}
	}
	return true;
}

UINT UserInputEventPump::MainLoop()
{
	UINT	IdleCount = 0;

	MSG msg;
	msg.wParam = 0;

	UserInputEvent	e;
	e.Device = UIDEV_VIEWPORT;
	e.Type = UIEVT_VIEWPORT_IDLE;

	for(;;)
	{
		while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)goto CRLA_END_OF_APP;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			IdleCount = 0;
		}

#ifdef _MFC_
		if(::AfxGetApp())
			AfxGetApp()->OnIdle(IdleCount);  // process idle for MFC threading model
#endif // #ifdef _MFC_

		e.Count = IdleCount++;
		e.Timestamp = _Timer.TimeLapse();
		_DispatchEvent(e);
	}

CRLA_END_OF_APP:
	return (UINT)msg.wParam;
}

LRESULT	UserInputEventPump::_WndProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ASSERT(_WndProc_Org);

	if(_DeviceInterested & UIDEV_MOUSE)
	{
		if(message == WM_PAINT)
		{
			UserInputEvent	e;
			e.Device = UIDEV_VIEWPORT;
			e.Type = UIEVT_VIEWPORT_REDRAW;
			e.Timestamp = _Timer.TimeLapse();
			_DispatchEvent(e);
		}
		else if(message == WM_SIZE)
		{
			int w = LOWORD(lParam);
			int h = HIWORD(lParam);
			if(	w && h && 
				(w != _LastViewportWidth || h != _LastViewportHeight)
			)
			{	_LastViewportWidth = w;
				_LastViewportHeight = h;

				UserInputEvent	e;
				e.Device = UIDEV_VIEWPORT;
				e.Type = UIEVT_VIEWPORT_RESIZE;
				e.Timestamp = _Timer.TimeLapse();
				e.Size.width = _LastViewportWidth;
				e.Size.height = _LastViewportHeight;
				_DispatchEvent(e);
			}
		}
		else if(message >= WM_MOUSEFIRST && message <= WM_MOUSELAST)
		{
			int x = (SHORT)LOWORD(lParam);
			int y = (SHORT)HIWORD(lParam);
			DWORD butcode = wParam&0x3;
			
			UserInputEvent	e;
			e.Device = UIDEV_MOUSE;
			e.ButtonCode = butcode;
			e.Timestamp = _Timer.TimeLapse();
			e.Position.x = x;
			e.Position.y = y;

			switch(message)
			{
			case WM_MOUSEMOVE:
				if(butcode == _MouseDragKeycode)
				{
					e.Type = _MouseDragKeycode?UIEVT_MOUSE_DRAG:UIEVT_MOUSE_MOVE;
				}
				else if(_MouseDragKeycode == 0)
				{
					_MouseDragKeycode = butcode;
					e.Type = UIEVT_MOUSE_DRAGBEGIN;
				}
				else
				{	e.Type = UIEVT_MOUSE_MOVE;
				}
				break;
			case WM_LBUTTONDOWN:
				e.Type = UIEVT_MOUSE_DOWN;
				e.ButtonCode = BUTTON_MOUSE_LEFT;
				::SetCapture(_Wnd_Subclassed);
				break;
			case WM_RBUTTONDOWN:
				e.Type = UIEVT_MOUSE_DOWN;
				e.ButtonCode = BUTTON_MOUSE_RIGHT;
				::SetCapture(_Wnd_Subclassed);
				break;
			case WM_LBUTTONUP:
				if(_MouseDragKeycode & BUTTON_MOUSE_LEFT)
				{	_MouseDragKeycode = 0;
					e.Type = UIEVT_MOUSE_DRAGEND;
					::ReleaseCapture();
					_DispatchEvent(e);
				}
				e.Type = UIEVT_MOUSE_UP;
				e.ButtonCode = BUTTON_MOUSE_LEFT;
				break;
			case WM_RBUTTONUP:
				if(_MouseDragKeycode & BUTTON_MOUSE_RIGHT)
				{	_MouseDragKeycode = 0;
					e.Type = UIEVT_MOUSE_DRAGEND;
					::ReleaseCapture();
					_DispatchEvent(e);
				}
				e.Type = UIEVT_MOUSE_UP;
				e.ButtonCode = BUTTON_MOUSE_RIGHT;
				break;
			case WM_MOUSEWHEEL:
				e.Type = UIEVT_MOUSE_WHEEL;
				e.Delta = GET_WHEEL_DELTA_WPARAM(wParam);
				break;
			}
			if(e.Type != UIEVT_MOUSE_MOVE || (UIDEV_EVENTTYPE_MOUSEMOVE&_DeviceInterested))
				_DispatchEvent(e);
		}
		else if(message == WM_KEYDOWN || message == WM_KEYUP)
		{
			UserInputEvent	e;
			e.Device = UIDEV_KEYBOARD;
			e.Timestamp = _Timer.TimeLapse();
			e.KeyCode = 0xff&wParam;
			e.Type = UIEVT_KEY_DOWN + (message - WM_KEYDOWN);

			_DispatchEvent(e);
		}
	}

	return CallWindowProc(_WndProc_Org, wnd, message, wParam, lParam);
}

} // namespace os


#elif defined(PLATFORM_MAC) || defined(PLATFORM_IOS)

namespace os
{

#if defined(PLATFORM_MAC)
UINT UserInputEventPump::MainLoop()
{
	os::UserInputEvent e;
	e.Device = os::UIDEV_VIEWPORT;
	e.Type = os::UIEVT_VIEWPORT_IDLE;
	
	UINT idlecount = 0;
	bool quit = false;
	while (!quit)
	{
		if(_objc_pumpevents())idlecount = 0;
		e.Count = idlecount++;
		_OnReceiveEventFromResponder(e);
	}
	
	return 0;
}
#endif
	
bool UserInputEventPump::Init(LPVOID pView, DWORD device_interested)
{
	_DeviceInterested = device_interested;
	if(0 == (UIDEV_MASK_MOBILE & device_interested)){}
	else return false;
	
	os::UserInputEvent e;
	_objc_view_get_size(pView, &e.Size.width, &e.Size.height);
	e.Device = os::UIDEV_VIEWPORT;
	e.Type = os::UIEVT_VIEWPORT_RESIZE;
	_OnReceiveEventFromResponder(e);
	
#if defined(PLATFORM_MAC)
	if(UIDEV_EVENTTYPE_MOUSEMOVE&device_interested)
		_objc_view_accept_mousemove(pView, true);
#endif
	
	return true;
}
	
void UserInputEventPump::_OnReceiveEventFromResponder(UserInputEvent& e)
{
	e.Timestamp = _Timer.TimeLapse();
	if(e.Device == os::UIDEV_MOUSE)
	{
		#if defined(PLATFORM_MAC)
		e.Position.y = _ViewHeight - e.Position.y;
		#endif
		if(!_bDragging && e.Type == os::UIEVT_MOUSE_DRAG)
		{	_bDragging = true;
			e.Type = os::UIEVT_MOUSE_DRAGBEGIN;
		}
		else if(_bDragging && e.Type != os::UIEVT_MOUSE_DRAG)
		{	_bDragging = false;
			DWORD t = e.Type;
			e.Type = os::UIEVT_MOUSE_DRAGEND;
			_DispatchEvent(e);
			e.Type = t;
		}
	}
	#if defined(PLATFORM_MAC)
	else if(e.Type == os::UIEVT_VIEWPORT_RESIZE)
	{
		_ViewHeight = e.Size.height;
	}
	#endif
	_DispatchEvent(e);
}
	
} // namespace os
#elif defined(PLATFORM_ANDROID)
	ASSERT_STATIC_NOT_IMPLMENTED;
#else
	ASSERT_STATIC_NOT_IMPLMENTED;
#endif

