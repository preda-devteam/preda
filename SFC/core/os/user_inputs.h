#pragma once
/**
 * @file user_inputs.h
 * @author SFC dev team
 * @brief 
 * @version 1.0
 * @date 2021-04-30
 * 
 * @copyright  
 * System Foundation Classes(SFC)
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *      * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials provided
 *        with the distribution.
 *      * Neither the name of SFC.  nor the names of its
 *        contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */
/** \defgroup os os
 * @ingroup SFC
 *  @{
 */
#ifdef _MFC_
#include <afxwin.h>
#endif
#include "predefines.h"
#include "../rt/buffer_type.h"
#include "../rt/small_math.h"
#include "kernel.h"


namespace os
{
/** \defgroup user_inputs user_inputs
 * @ingroup os
 *  @{
 */
enum _tagUserInputDevice
{
	UIDEV_SYS				= 0x0000,
	UIDEV_VIEWPORT			= 0x0001,
	UIDEV_KEYBOARD			= 0x0002,
	UIDEV_MOUSE				= 0x0004,
	UIDEV_TOUCH				= 0x0004,
    UIDEV_COMMAND           = 0x0008,
	UIDEV_MULTITOUCH		= 0x0010,
	UIDEV_CONTROL_BUTTONS	= 0x0020,	///< remote controler, button-like gesture or built-in buttons
	UIDEV_ACCELEROMETER		= 0x0040,
	UIDEV_MAGNETIC_FIELD	= 0x0100,
	UIDEV_GYROSCOPE			= 0x0200,
	UIDEV_AMBINET_LIGHT		= 0x0400,

	UIDEV_MASK_DESKTOP		= 0x000f,
	UIDEV_MASK_MOBILE		= 0x07f0,
	UIDEV_MASK_TOUCH		= 0x0030,
    UIDEV_MASK_ALL          = 0xffff,
	
	UIDEV_EVENTTYPE_MOUSEMOVE = 0x0001000, ///< specify this to receive Mouse move
};

enum _tagPollButtonCode
{
	BUTTON_MOUSE_LEFT	= 0x0001,
	BUTTON_MOUSE_RIGHT	= 0x0002,
	BUTTON_KB_CONTROL	= 0x0010,
	BUTTON_KB_SHIFT		= 0x0020,
	BUTTON_KB_ALT		= 0x0040,

	BUTTON_MOUSE_MASK	= 0x000f,
	BUTTON_KB_MASK		= 0x00f0,

	BUTTON_TOUCH		= 0x0001
};

enum _tagSysCode
{	
	SC_SUBSCRIBED	= 1,
	SC_UNSUBSCRIBED	= 2,
};

enum _tagKeyCode
{
	KC_NUMPAD0				= 0x60,
	KC_NUMPAD1				= 0x61,
	KC_NUMPAD2				= 0x62,
	KC_NUMPAD3				= 0x63,
	KC_NUMPAD4				= 0x64,
	KC_NUMPAD5				= 0x65,
	KC_NUMPAD6				= 0x66,
	KC_NUMPAD7				= 0x67,
	KC_NUMPAD8				= 0x68,
	KC_NUMPAD9				= 0x69,
	KC_MULTIPLY				= 0x6A,
	KC_ADD					= 0x6B,
	KC_SEPARATOR			= 0x6C,
	KC_SUBTRACT				= 0x6D,
	KC_DECIMAL				= 0x6E,
	KC_DIVIDE				= 0x6F,
	KC_F1					= 0x70,
	KC_F2					= 0x71,
	KC_F3					= 0x72,
	KC_F4					= 0x73,
	KC_F5					= 0x74,
	KC_F6					= 0x75,
	KC_F7					= 0x76,
	KC_F8					= 0x77,
	KC_F9					= 0x78,
	KC_F10					= 0x79,
	KC_F11					= 0x7A,
	KC_F12					= 0x7B,
	KC_F13					= 0x7C,
	KC_F14					= 0x7D,
	KC_F15					= 0x7E,
	KC_F16					= 0x7F,
	KC_F17					= 0x80,
	KC_F18					= 0x81,
	KC_F19					= 0x82,
	KC_F20					= 0x83,
	KC_F21					= 0x84,
	KC_F22					= 0x85,
	KC_F23					= 0x86,
	KC_F24					= 0x87,
	KC_NUMLOCK				= 0x90,
	KC_SCROLLLOCK			= 0x91,
	KC_LSHIFT				= 0xA0,
	KC_RSHIFT				= 0xA1,
	KC_LCONTROL				= 0xA2,
	KC_RCONTROL				= 0xA3,
	KC_LALT					= 0xA4,
	KC_RALT					= 0xA5,
	KC_BROWSER_BACK			= 0xA6,
	KC_BROWSER_FORWARD		= 0xA7,
	KC_BROWSER_REFRESH		= 0xA8,
	KC_BROWSER_STOP			= 0xA9,
	KC_BROWSER_SEARCH		= 0xAA,
	KC_BROWSER_FAVORITES	= 0xAB,
	KC_BROWSER_HOME			= 0xAC,
	KC_VOLUME_MUTE			= 0xAD,
	KC_VOLUME_DOWN			= 0xAE,
	KC_VOLUME_UP			= 0xAF,
	KC_MEDIA_NEXT_TRACK		= 0xB0,
	KC_MEDIA_PREV_TRACK		= 0xB1,
	KC_MEDIA_STOP			= 0xB2,
	KC_MEDIA_PLAY_PAUSE		= 0xB3,
	KC_LAUNCH_MAIL			= 0xB4,
	KC_LAUNCH_MEDIA_SELECT	= 0xB5,
	KC_LAUNCH_APP1			= 0xB6,
	KC_LAUNCH_APP2			= 0xB7,
	KC_OEM_RESET			= 0xE9,
	KC_OEM_JUMP				= 0xEA,
	KC_OEM_PA1				= 0xEB,
	KC_OEM_PA2				= 0xEC,
	KC_OEM_PA3				= 0xED,
	KC_OEM_WSCTRL			= 0xEE,
	KC_OEM_CUSEL			= 0xEF,
	KC_OEM_ATTN				= 0xF0,
	KC_OEM_FINISH			= 0xF1,
	KC_OEM_COPY				= 0xF2,
	KC_OEM_AUTO				= 0xF3,
	KC_OEM_ENLW				= 0xF4,
	KC_OEM_BACKTAB			= 0xF5,
	KC_ATTN					= 0xF6,
	KC_CRSEL				= 0xF7,
	KC_EXSEL				= 0xF8,
	KC_EREOF				= 0xF9,
	KC_PLAY					= 0xFA,
	KC_ZOOM					= 0xFB,
	KC_NONAME				= 0xFC,
	KC_PA1					= 0xFD,
	KC_OEM_CLEAR			= 0xFE
};
class UserInputState	
{
public:
	static bool		InitDevices(DWORD devices);
	static DWORD	GetDevicePresence();
	static bool		GetMousePosition(int* xy);	///< {x,y}[], screen space
	static DWORD	GetPollButtonState(DWORD button_interested);
};
struct UserInputEvent
{
	ULONGLONG	Timestamp;	///< in nanosec
	DWORD		Type;
	DWORD		Device;
	union
	{
		struct
		{	int		x;
			int		y;
			template<typename T> void CopyFrom(const T& p){ x = (int)p.x; y = (int)p.y; }
			template<typename T> void CopyTo(T& p) const { p.x = x; p.y = y; }
		} Position;
		struct
		{	int		width;
			int		height;
			template<typename T> void CopyFrom(const T& p){ width = (int)p.width; height = (int)p.height; }
			template<typename T> void CopyTo(const T& p){ p.width = width; p.height = height; }
		} Size;
		UINT	Count;
        LPVOID  Param;
	};
	union
	{   DWORD   CmdId;
        DWORD	KeyCode;
		DWORD	SysCode;
		DWORD	ButtonCode;
		int		Delta;
	};
	void Log() const;
};

enum _tagEventType
{
	UIEVT_SYS		= 0,	///< SysCode
    UIEVT_COMMAND,          ///< CmdId, Param
	UIEVT_KEY_DOWN,			///< KeyCode
	UIEVT_KEY_UP,			///< KeyCode

	UIEVT_MOUSE_DOWN,		///< Position, ButtonCode
	UIEVT_MOUSE_UP,			///< Position, ButtonCode
	UIEVT_MOUSE_MOVE,		///< Position
	UIEVT_MOUSE_DRAGBEGIN,	///< Position, ButtonCode
	UIEVT_MOUSE_DRAG,		///< Position, ButtonCode
	UIEVT_MOUSE_DRAGEND,	///< Position, ButtonCode
	UIEVT_MOUSE_WHEEL,		///< Position, Delta

	UIEVT_VIEWPORT_RESIZE,	///< Size
	UIEVT_VIEWPORT_REDRAW,	///< n/a
	UIEVT_VIEWPORT_IDLE,	///< Count

	UIEVT_TOUCH_BEGIN = UIEVT_MOUSE_DRAGBEGIN,	
	UIEVT_TOUCH_END = UIEVT_MOUSE_DRAGEND,		
	UIEVT_TOUCH_DRAG = UIEVT_MOUSE_DRAG,	
};

struct UserInputSubscriber
{
	virtual void OnUserInputEvent(const UserInputEvent& x) = 0;
};

class UserInputEventPump
{
	const UserInputEvent*			_pCurrentEvent;
	static UserInputEventPump*		g_pSingletone;
	struct _eventhandler
	{	UserInputSubscriber*		pHandler;
		DWORD						DeviceMask;
	};
protected:
	rt::BufferEx<_eventhandler>		_Handlers;
	DWORD							_DeviceInterested;
	int								_LastViewportWidth;
	int								_LastViewportHeight;
	os::HighPerformanceCounter		_Timer;

	void	_DispatchEvent(const UserInputEvent& x);
	
public:
	static UserInputEventPump* Get(){ return g_pSingletone; }
	UserInputEventPump();
	~UserInputEventPump(){ Term(); g_pSingletone = nullptr; }
	void	AddSubscriber(UserInputSubscriber* h, DWORD device_interested = UIDEV_MASK_ALL);
	void	RemoveSubscriber(UserInputSubscriber* h);
	void	Term();
    
    void    SendEvent(UserInputEvent& e);
    void    SendEvent_Command(DWORD cmdid, LPVOID param = nullptr);


	INLFUNC const UserInputEvent* GetCurrentEvent() const { return _pCurrentEvent; }
	INLFUNC	bool IsMouseMoveInterested() const { return 0 != (_DeviceInterested&UIDEV_EVENTTYPE_MOUSEMOVE); }
	INLFUNC bool IsMultiTouchInterested() const { return 0 != (_DeviceInterested&UIDEV_MULTITOUCH); }
	
#if defined(PLATFORM_WIN)
	bool	Init(HWND wnd, DWORD device_interested = UIDEV_MASK_ALL);
	UINT	MainLoop();
protected:
	DWORD	_MouseDragKeycode;
	HWND	_Wnd_Subclassed;
	WNDPROC	_WndProc_Org;
	LRESULT	_WndProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam);
protected:
#elif defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
	UINT	MainLoop();
	#if defined(PLATFORM_MAC)
	int		_ViewHeight;
	#endif
	bool	_bDragging;
public:
	bool	Init(LPVOID pView, DWORD device_interested = UIDEV_MASK_ALL); // pView should be NSView in Mac and UIView in iOS
	void	_OnReceiveEventFromResponder(UserInputEvent& x);
	long	_rolloverTrackingRectTag;
#else
	ASSERT_STATIC(0);
#endif
};
/** @}*/
} // namespace os


#if defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
/////////////////////////////////////////
// BIND_UIEVENTPUMP

#define MOUSE_EVENT_RESPONSE(PUMP,MSG, TYPE, BUTTON) \
- (void) MSG:(NSEvent *)te	\
{	os::UserInputEvent e;	\
e.Device = os::UIDEV_MOUSE; \
e.Type = os::TYPE;		\
e.Position.CopyFrom([te locationInWindow]);	\
e.ButtonCode = os::BUTTON;				\
PUMP._OnReceiveEventFromResponder(e);	\
}

#define MOUSE_MOVE_RESPONSE(PUMP,MSG, TYPE) \
- (void)MSG:(NSEvent *)te \
{	os::UserInputEvent e; \
e.Device = os::UIDEV_MOUSE; \
e.Type = os::TYPE; \
e.Position.CopyFrom([te locationInWindow]); \
e.ButtonCode = (DWORD)(0x3&[NSEvent pressedMouseButtons]); \
PUMP._OnReceiveEventFromResponder(e); \
}

#define BIND_UIEVENTPUMP(PUMP) \
MOUSE_EVENT_RESPONSE(PUMP,mouseDown, UIEVT_MOUSE_DOWN, BUTTON_MOUSE_LEFT)			\
MOUSE_EVENT_RESPONSE(PUMP,mouseUp, UIEVT_MOUSE_UP, BUTTON_MOUSE_LEFT)				\
MOUSE_EVENT_RESPONSE(PUMP,rightMouseDown, UIEVT_MOUSE_DOWN, BUTTON_MOUSE_RIGHT)		\
MOUSE_EVENT_RESPONSE(PUMP,rightMouseUp, UIEVT_MOUSE_UP, BUTTON_MOUSE_RIGHT)			\
MOUSE_MOVE_RESPONSE(PUMP,mouseMoved, UIEVT_MOUSE_MOVE)								\
MOUSE_MOVE_RESPONSE(PUMP,mouseDragged, UIEVT_MOUSE_DRAG)							\
MOUSE_MOVE_RESPONSE(PUMP,rightMouseDragged, UIEVT_MOUSE_DRAG)						\
- (void)scrollWheel:(NSEvent *)te								\
{	os::UserInputEvent e;	e.Device = os::UIDEV_MOUSE;			\
e.Type = os::UIEVT_MOUSE_WHEEL;									\
e.Position.CopyFrom([te locationInWindow]);						\
e.Delta = [te scrollingDeltaY]*200;								\
PUMP._OnReceiveEventFromResponder(e);							\
}																\
- (void) keyDown:(NSEvent *)te									\
{	os::UserInputEvent e;	e.Device = os::UIDEV_KEYBOARD;		\
e.Type = os::UIEVT_KEY_DOWN;									\
e.KeyCode = [te keyCode];										\
PUMP._OnReceiveEventFromResponder(e);							\
}																\
- (void) keyUp:(NSEvent *)te									\
{	os::UserInputEvent e;	e.Device = os::UIDEV_KEYBOARD;		\
e.Type = os::UIEVT_KEY_UP;										\
e.KeyCode = [te keyCode];										\
PUMP._OnReceiveEventFromResponder(e);							\
}																\
- (void) setFrame: (NSRect) frame								\
{	[super setFrame: frame];									\
os::UserInputEvent e;	e.Device = os::UIDEV_VIEWPORT;			\
e.Type = os::UIEVT_VIEWPORT_RESIZE;								\
e.Size.CopyFrom(frame.size);									\
PUMP._OnReceiveEventFromResponder(e);							\
}																\
- (void) drawRect:(NSRect)dirtyRect								\
{	os::UserInputEvent e;										\
e.Device = os::UIDEV_VIEWPORT;									\
e.Type = os::UIEVT_VIEWPORT_REDRAW;								\
PUMP._OnReceiveEventFromResponder(e);							\
}																\
- (bool)acceptsFirstResponder{ return true; }					\
- (void)clearTrackingRect										\
{   if (PUMP._rolloverTrackingRectTag > 0)						\
    {   [self removeTrackingRect:PUMP._rolloverTrackingRectTag];\
        PUMP._rolloverTrackingRectTag = 0;						\
}   }															\
- (void)resetTrackingRect										\
{   [self clearTrackingRect];									\
    PUMP._rolloverTrackingRectTag =								\
	[self addTrackingRect:[self visibleRect] owner:self userData:NULL assumeInside:NO];	\
}																\
- (void)resetCursorRects										\
{   [super resetCursorRects];									\
    [self resetTrackingRect];									\
}																\
- (void)viewDidMoveToWindow										\
{   if ([self window]){ [self resetTrackingRect]; }				\
}																\
- (void)mouseEntered:(NSEvent *)theEvent						\
{	if(PUMP.IsMouseMoveInterested())							\
	{	[ [self window] setAcceptsMouseMovedEvents:YES];		\
		[ [self window] makeFirstResponder:self];				\
}	}															\
- (void)mouseExited:(NSEvent *)theEvent							\
{   if(PUMP.IsMouseMoveInterested())							\
		[[self window] setAcceptsMouseMovedEvents:NO];			\
}

#endif
/** @}*/
