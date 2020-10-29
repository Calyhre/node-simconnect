#ifndef SIMCONNECT_SESSION_H
#define SIMCONNECT_SESSION_H

#include <string>
#include <vector>
#include <map>
#include <windows.h>

#include "commons.h"

struct SIMCONNECT_RECV;
struct DataBatchDefinition;

class SimConnectSession {

public:
    SimConnectSession();
    bool Open(const std::string& appName);
    bool Close();

    DispatchContent NextDispatch();

    unsigned int SubscribeToSystemEvent(const std::string& eventName);
    unsigned int RequestDataOnSimObject(unsigned int existingDataDefinitionId, unsigned int objectId, unsigned int period, unsigned int flags);
    unsigned int RequestDataOnSimObject(std::vector<DatumRequest> datumRequests, unsigned int objectId, unsigned int period, unsigned int flags);
    unsigned int RequestDataOnSimObjectType(std::vector<DatumRequest> datumRequests, unsigned int radius, unsigned int simobjectType);
    unsigned int SetDataOnSimObject(std::string datumName, std::string unitsName, double value);
    unsigned int SetAircraftInitialPosition(
        double lat,
        double lng,
        double altitude,
        double pitch,
        double bank,
        double heading,
        bool onGround,
        unsigned long airspeed
    );
    unsigned int RequestSystemState(std::string stateName);
    unsigned int FlightLoad(std::string fileName);
    unsigned int TransmitClientEvent(std::string eventName, unsigned int objectId, int data);
    unsigned int CreateDataDefinition(std::vector<DatumRequest> datumRequests);

    void ErrorReported();
   
private:
    HANDLE hSimConnect;
    ErrorInfo* fatalError;

    DispatchContent Process(SIMCONNECT_RECV* pData, DWORD cbData);
    void HandleError(const std::string& name, NTSTATUS code);

    ExceptionInfo* GetExceptionInfo(SIMCONNECT_RECV *pData);
    SimEvent* GetEvent(SIMCONNECT_RECV *pData);
    SimInfo* GetSimInfo(SIMCONNECT_RECV *pData);
    SimSystemState* GetSystemState(SIMCONNECT_RECV *pData);
    SimobjectDataBatch* GetSimObjectData(SIMCONNECT_RECV *pData, DWORD cbData);
    DataBatchDefinition GenerateDataDefinition(std::vector<DatumRequest> datumRequests);
};



#endif