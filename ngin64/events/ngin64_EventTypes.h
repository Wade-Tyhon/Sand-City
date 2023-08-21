#ifndef NGIN64_EVENTTYPES_H
#define NGIN64_EVENTTYPES_H



#include <stdarg.h>


#include "../nGin64.h"
#include "../gui/ngin64_GUI_Types.h"

#define BIT(x) (1 << x) //Note - allow an event type to belong to different categories









enum g64_PlayfieldState {

    NoInt,

};


typedef struct {
    bool trigger;
    bool constTrigger;
    int i[3];
    float f[3];
    g64_GameTimer time;
    char key[12];
    char* keyB;
} g64_EventArgs;

extern g64_EventArgs defaultArgs;

typedef struct {
    char* name;
    //void (*listenerFunc)();
    void(*listenerFunc)(g64_EventArgs*);
}g64_EventListeners;

typedef struct {
    char* name;
    //g64_EventType* type;
    g64_EventArgs args;
    //g64_EventHandler* handler;
    void (*handlerFunc)();
    g64_EventListeners listeners[10];
} g64_Event;


typedef struct {
    
    char* name;
    CursorObject* Cursor;
    g64_GameTimer eventDelay;
    //enum g64_EventType GUI_State;
    /*
    g64_Event OnHover;
    g64_Event OnClick;    
    g64_Event OnHold;
    g64_Event OnRelease;
    */
    enum g64_PlayfieldState state;
    //g64_Event 

    g64_EventListeners listeners[10];
    
}g64_GUIEvent;


typedef struct {
    //bool activate;
    char* name;
    CursorObject* Cursor;
    g64_Event OnTrigger; //holds arguments, handler and 
    g64_Event OnCompletion; //holds arguments, handler and 
    g64_EventListeners listeners[10];
    //enum g64_PlayfieldEventState* state;
}g64_PlayfieldEvent;











































typedef struct {
    //Note ----- general info and settings for each g64_TimeEvent event
    char* name;
    bool loop;
    g64_GameTimer timerLength;

    //Note ----- g64_Event holds event trigger args and subscribers:
    g64_Event OnTimerStart; //
    g64_Event OnTimerEnd;
}g64_TimeEvent;





extern bool gin64_TimeEvent_Init(g64_TimeEvent* timeEvent);
//extern bool gin64_TimeEvent_Init(g64_TimeEvent timeEvent);
extern bool gin64_GUIEvent_Init(g64_GUIEvent* guiEvent);


extern void gin64_Event_Subscribe(g64_Event* thisEvent, void(*listenerFunction));
extern void gin64_TimeEvents_Subscribe(g64_TimeEvent* timeEvent, void(*listenerFunction));
extern void gin64_GUIEvents_Subscribe(g64_GUIEvent* guiEvent, void(*listenerFunction));
//extern void gin64_Events_Update(g64_TimeEvent* timeEvent);
extern void gin64_Events_Update();
extern void gin64_TimeEvent_Set(char* name, g64_TimeEvent* timeEvent, g64_GameTimer timerLength, bool loopEvent);
//extern void gin64_GUIEvent_Set(char* name, g64_GUIEvent* guiEvent, CursorObject* cursor, void(*handlerFunction));

extern bool gin64_PlayfieldEvent_Init(g64_PlayfieldEvent* playfieldEvent);

extern void gin64_PlayfieldEvent_Set(char* name, g64_PlayfieldEvent* playfieldEvent, CursorObject* cursor, void(*handlerFunction));
//extern bool gin64_GUIEvent_Init(g64_GUIEvent timeEvent);



#define gin64_ForEach(listener, listenerGroup) \
    for(int keep = 1, count = 0, size = sizeof(listenerGroup) / sizeof(listenerGroup[0]); \
    keep && count != size; \
    keep = !keep, count++) \
    for(listener = listenerGroup[count]; keep; keep = !keep)

    //for(T*item = listenerGroup->head; item != NULL; item = item->next)

#define gin64_Event_Init(event) _Generic((event), \
    g64_TimeEvent*: gin64_TimeEvent_Init, \
    g64_GUIEvent*: gin64_GUIEvent_Init, \
    g64_PlayfieldEvent*: gin64_PlayfieldEvent_Init, \
    default: gin64_GUIEvent_Init \
    )(event)



#endif
