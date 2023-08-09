#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <sys/select.h>
#include <stdarg.h>

#include "../nGin64.h"

//#include "ngin64_EventTypes.h"



/*----- Note -----  Complete a timer function in 'ngin64_SystemFunc' named 'short gin64_Time()'
                        - Once complete, test the new event type 'g64_TimeEvent' by setting a "start time" and assign a "complete time"
                        - in each scripts *_Init function, subscribe to each time events and set up handler functions
                        - Once the time is completed, fire off the event and send messages to all functions subscribed to this event
                        - Set the event timer in SandCity_Main for now and test the process...
                        - The event timer and listeners are working!! 
                            - finalize the process for creating events, subscribing to events, etc to make it easier to remember. 
*/




g64_GUIEvent OpenTileStats;
g64_TimeEvent CollectTaxes;


g64_GUIEvent* ActiveGUIEvents[10];
g64_PlayfieldEvent* ActivePlayfieldEvents[10];
g64_TimeEvent* ActiveTimeEvents[10];

g64_GameTimer currentTime;
bool testEvent = false;


void gin64_GUIEvent_Handler(g64_GUIEvent* guiEvent);
void gin64_TimeEvent_Handler(g64_TimeEvent* timeEvent);


extern CursorObject playfieldCursor;

g64_EventArgs defaultArgs = {
    false,
    {0,0,0},
    {0.0f, 0.0f, 0.0f},
    {0, 0, 0.0f}
};


bool gin64_TimeEvent_Init(g64_TimeEvent* timeEvent) {
    //fprintf(stderr, "\nGeneric Function Macro 'gin64_Event_Init' Has Called 'gin64_TimeEvent_Init(g64_TimeEvent timeEvent)'\n\n");
    
    //----- Note ----- Set up default values for a new event and add it to the list of events for updating    
    char* name = "Time Event Default";

    //----- Note ----- Arguments that can be used to test whether an event has been triggered or not
    timeEvent->OnTimerStart.args.trigger = false; 

    timeEvent->OnTimerStart.args.i[0] = 0;
    timeEvent->OnTimerStart.args.i[1] = 0;
    timeEvent->OnTimerStart.args.i[2] = 0;

    timeEvent->OnTimerStart.args.f[0] = 0.001f;
    timeEvent->OnTimerStart.args.f[1] = 0.001f;
    timeEvent->OnTimerStart.args.f[2] = 0.001f;

    timeEvent->OnTimerEnd = timeEvent->OnTimerStart;
     
    for (int i = 0; i < 9; i++)
    {

        if (ActiveTimeEvents[i] == NULL) {

            ActiveTimeEvents[i] = timeEvent; //Add to the list of active time events
            break;
        }
    }


    return true;
}

void gin64_TimeEvent_Set(char *name, g64_TimeEvent* timeEvent, g64_GameTimer timerLength, bool loopEvent) {

    timeEvent->name = name;

    timeEvent->timerLength = timerLength;
    currentTime = gin64_GetGameTime(); //Get the current starting time

    timeEvent->loop = loopEvent;

    timeEvent->OnTimerStart.args.trigger = true;

    timeEvent->OnTimerStart.args.time = currentTime;

    timeEvent->OnTimerEnd.args.trigger = false;

    timeEvent->OnTimerEnd.args.time = gin64_AddGameTimers( currentTime, timerLength);

}


bool gin64_PlayfieldEvent_Init(g64_PlayfieldEvent* playfieldEvent) {

    for (int i = 0; i < 9; i++)
    {
        if (ActivePlayfieldEvents[i] == NULL) {

            ActivePlayfieldEvents[i] = playfieldEvent; //Add to the list of active time events
            break;
        }
    }
    return true;
}


void gin64_PlayfieldEvent_Set(char* name, g64_PlayfieldEvent* playfieldEvent, CursorObject* cursor, void(*handlerFunction)) {
    currentTime = gin64_GetGameTime(); //Get the current starting time

    playfieldEvent->name = name;
    playfieldEvent->Cursor = cursor;
    playfieldEvent->OnTrigger.args = defaultArgs;
    playfieldEvent->OnTrigger.handlerFunc = handlerFunction;

}


bool gin64_GUIEvent_Init(g64_GUIEvent* guiEvent) {

    return true;
}
void gin64_GUIEvent_Set(char *name, g64_GUIEvent* guiEvent, g64_GameTimer timerLength, CursorObject* cursor) {

    currentTime = gin64_GetGameTime(); //Get the current starting time

}

void gin64_Events_Update(){

    currentTime = gin64_GetGameTime(); //Get the current starting time


    for (int i = 0; i < 9; i++) {

        if (ActiveTimeEvents[i]) {

            if (ActiveTimeEvents[i]->OnTimerEnd.listeners[0].listenerFunc == NULL)
                fprintf(stderr, "\n\n--------\n!!! No Listeners !!! \n--------\n\n");
            //fprintf(stderr, "\n\n--------\n!!!Timer Event Check!!! %f'\n--------\n\n", ActiveTimeEvents[i]->OnTimerEnd.args.time.seconds);

            if (currentTime.hours >= ActiveTimeEvents[i]->OnTimerEnd.args.time.hours){
                if (currentTime.minutes >= ActiveTimeEvents[i]->OnTimerEnd.args.time.minutes){
                    if (currentTime.seconds >= ActiveTimeEvents[i]->OnTimerEnd.args.time.seconds){
                        ActiveTimeEvents[i]->OnTimerEnd.args.trigger = true;
                    }
                }
            }

            if (ActiveTimeEvents[i]->OnTimerEnd.args.trigger) {
                

                //----- Note ----- The following 'ForEachListener' macro iterates through each listener that has subscribed to this event.
                gin64_ForEach(g64_EventListeners templistener, ActiveTimeEvents[i]->OnTimerEnd.listeners) {
                    if(templistener.listenerFunc)
                        templistener.listenerFunc(&ActiveTimeEvents[i]->OnTimerEnd.args); //Note - Call each listener in the array
                }

                ActiveTimeEvents[i]->OnTimerEnd.args.trigger = false;
                //----- Note ----- If this element is set to loop repeatedly, reset this event to it's default state
                if (ActiveTimeEvents[i]->loop)
                    gin64_TimeEvent_Set(ActiveTimeEvents[i]->name, ActiveTimeEvents[i], ActiveTimeEvents[i]->timerLength, ActiveTimeEvents[i]->loop);

                
            }
        }

        if (ActiveGUIEvents[i]) {

        }

        if (ActivePlayfieldEvents[i]) {

            ActivePlayfieldEvents[i]->OnTrigger.handlerFunc(&ActivePlayfieldEvents[i]->OnTrigger, ActivePlayfieldEvents[i]->name);

                if (ActivePlayfieldEvents[i]->OnTrigger.args.trigger == true) {

                    if (ActivePlayfieldEvents[i]->OnTrigger.listeners[0].listenerFunc == NULL) {
                        //fprintf(stderr, "\n\n--------\n!!! No Playfield Listeners !!! \n--------\n\n");
                    }

                    else{
                        gin64_ForEach(g64_EventListeners templistener, ActivePlayfieldEvents[i]->OnTrigger.listeners) {
                            if (templistener.listenerFunc)
                                templistener.listenerFunc(&ActivePlayfieldEvents[i]->OnTrigger.args); //Note - Call each listener in the array
                        }

                    }


                    if (ActivePlayfieldEvents[i]->OnCompletion.listeners[0].listenerFunc == NULL) {
                        //fprintf(stderr, "\n\n--------\n!!! No Playfield Listeners !!! \n--------\n\n");
                    }
                    else {
                        gin64_ForEach(g64_EventListeners templistener, ActivePlayfieldEvents[i]->OnCompletion.listeners) {
                            if (templistener.listenerFunc)
                                templistener.listenerFunc(&ActivePlayfieldEvents[i]->OnCompletion.args); //Note - Call each listener in the array
                        }
                    }
                    ActivePlayfieldEvents[i]->OnTrigger.args.trigger = false;
                    //gin64_PlayfieldEvent_Set("Build Type", &ActiveTimeEvents[i], &playfieldCursor, &SC_BuildingType_Handler);
                    //gin64_PlayfieldEvent_Set(ActiveTimeEvents[i]->name, ActiveTimeEvents[i], ActiveTimeEvents[i]->timerLength, ActiveTimeEvents[i]->loop);
                }
            

            
        }

    }


}


void gin64_GUIEvent_Handler(g64_GUIEvent* guiEvent) {

}


void gin64_Event_Subscribe(g64_Event* thisEvent, void(*listenerFunction)) {
    //----- Note ----- For subscribing to a specific event rather than a collection of events

    for (int i = 0; i < 9; i++)
    {
        if (thisEvent->listeners[i].listenerFunc == NULL) {
            thisEvent->listeners[i].listenerFunc = listenerFunction; //Add to the list of active time events
            return;
        }
    }

}






















void gin64_TimeEvents_Subscribe(g64_TimeEvent* timeEvent, void(*listenerFunction)) {
    
    //----- Note ----- For subscribing to all events in this collection of timed events
    for (int i = 0; i < 9; i++)
    {
        if (timeEvent->OnTimerEnd.listeners[i].listenerFunc == NULL) {

            timeEvent->OnTimerEnd.listeners[i].listenerFunc = listenerFunction; //Add to the list of active time events
            return;
        }
    }

}


void gin64_GUIEvents_Subscribe(g64_GUIEvent* guiEvent, void(*listenerFunction)) {

    //guiEvent->listeners[0].listenerFunc = listenerFunction;

    for (int i = 0; i < 9; i++)
    {
        if (guiEvent->listeners[i].listenerFunc == NULL) {

            guiEvent->listeners[i].listenerFunc = listenerFunction; //Add to the list of active time events
            return;
        }
    }
}


void gin64_PlayfieldEvents_Subscribe(g64_PlayfieldEvent* playfieldEvent, void(*listenerFunction)) {

    //guiEvent->listeners[0].listenerFunc = listenerFunction;

    for (int i = 0; i < 9; i++)
    {
        if (playfieldEvent->OnTrigger.listeners[i].listenerFunc == NULL) {

            playfieldEvent->OnTrigger.listeners[i].listenerFunc = listenerFunction; //Add to the list of active time events
            return;
        }
    }
}


void gin64_TimeEvent_Handler(g64_TimeEvent* timeEvent){


}