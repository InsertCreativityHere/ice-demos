//
// Copyright (c) ZeroC, Inc. All rights reserved.
//

#include <Ice/Ice.h>
#include <Callback.h>
#include <mex.hpp>
#include <mexAdapter.hpp>
#include <MatlabDataArray.hpp>

using namespace std;
using namespace Demo;
using namespace matlab::data;

class CallbackReceiverI : public CallbackReceiver
{
public:
    CallbackReceiverI(const shared_ptr<matlab::engine::MATLABEngine>& matlabPtr) :
        _matlabPtr(matlabPtr),
        _index(_counter++)
    {
    }

    virtual void
    callback(Ice::Int num, const Ice::Current&) override
    {
        vector<Array> parameters = {ArrayFactory().createScalar(_index), ArrayFactory().createScalar(num)};

        // Forward the dispatch onto to resultCallback in MATLAB.
        // Only the main MexFunction thread can directly call into MATLAB synchronously,
        // so here we make an async call, then wait for it to complete.
        auto future = _matlabPtr->fevalAsync(u"resultCallback", 0, parameters);
        future.get();
    }

private:
    shared_ptr<matlab::engine::MATLABEngine> _matlabPtr;
    const int _index;
    static int _counter;
};
int CallbackReceiverI::_counter = 0;

// MATLAB's entry-point. MEX (MATLAB) always calls into "MexFunction.operator()"
class MexFunction : public matlab::mex::Function
{
public:
    MexFunction() :
        _matlabPtr(getEngine())
    {
    }

    // MEX passes a list of inputs and outputs C++ can access
    void
    operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) override
    {
        // For this demo, we pass the operation name as the first input argument.
        string opName = (static_cast<matlab::data::CharArray>(inputs[0])).toAscii();
        int returnVal = 0;
        if(opName == "addClient")
        {
            returnVal = addClientI();
        }
        else if(opName == "destroy")
        {
            returnVal = destroyI();
        }
        // Output the return value to MATLAB (0 for success, 1 for failure)
        // (First create a 1x1 array to put the return value in)
        auto returnArr = ArrayFactory().createArray<int>({1, 1});
        returnArr[0][0] = returnVal;
        outputs[0] = returnArr;
    }

    // Add this client to the server to receive callbacks from it.
    int
    addClientI()
    {
        // Initialize a new communicator if there isn't one already.
        if(!_ich)
        {
            // Initialize a communicator.
            _ich = Ice::initialize("config.client");

            // Obtain a proxy to the server.
            _serverProxy = Ice::checkedCast<CallbackSenderPrx>(_ich->propertyToProxy("CallbackSender.Proxy"));
            if(!_serverProxy)
            {
                cerr << "Invalid proxy" << endl;
                return 1;
            }
            // Create an anonymous object adapter for receiving callbacks.
            _adapter = _ich->createObjectAdapter("");
            // Register the object adapter with the bidirectional connection.
            _serverProxy->ice_getConnection()->setAdapter(_adapter);
        }

        // Send the request to the server
        try
        {
            auto callbackPrx = _adapter->addWithUUID(make_shared<CallbackReceiverI>(_matlabPtr));
            _clientProxy = Ice::uncheckedCast<CallbackReceiverPrx>(callbackPrx);
            _serverProxy->addClient(_clientProxy);
        }
        catch(const std::exception& ex)
        {
            cout << ex.what() << endl;
            return 1;
        }
        return 0;
    }

    // Destroy the client's communicator and perform cleanup
    int
    destroyI()
    {
        if(_ich)
        {
            _ich->destroy();
            _ich.release();
        }
        return 0;
    }

private:
    shared_ptr<matlab::engine::MATLABEngine> _matlabPtr;
    shared_ptr<Ice::ObjectAdapter> _adapter;
    shared_ptr<CallbackReceiverPrx> _clientProxy;
    shared_ptr<CallbackSenderPrx> _serverProxy;
    Ice::CommunicatorHolder _ich;
};
