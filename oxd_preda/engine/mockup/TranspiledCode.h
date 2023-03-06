namespace NS_MyDApp_Dev_6 {
static uint64_t *__prli___contract_slot = nullptr;
static uint32_t *__prli___asset_slot = nullptr;
struct __prlt_Dev {
    __prlt_map<__prlt_int32, __prlt_map<__prlt_uint8, __prlt_array<__prlt_int64>>> __prli_m_m;
    __prlt_array<__prlt_int32> __prli_m_ai;
    
    __prlt_uint16 __prli_f() {
        return __prlt_uint16(0);
    }
    void __prli_address_pulse_yield() const {
        //prlrt::relay_shard(3);
    }
    void __prli_pulse_yield() const {
        //prlrt::relay_shard(4);
        __prlt_address __prli_a;
        prlrt::relay(__prli_a, 5);
    }
    void __prli_deploy_yield() const {
    }
    void __prli_scaleout_yield(__prlt_bool __prli_a) const {
    }
    void __prli_g() {
        __prlt_int32 __prli_i;
        __prli_i = __prlt_int32(__prlt_uint8(1));
        __prlt_blob __prli_b = __prlt_blob();
        __prlt_address __prli_a = __prlt_address();
        __prlt_hash __prli_h1 = __prlt_hash();
        __prlt_array<__prlt_int32> __prli_ai;
        __prlt_map<__prlt_int32, __prlt_map<__prlt_uint8, __prlt_array<__prlt_int64>>> __prli_m;
    }
    void __prli_g(__prlt_uint32 __prli_u32) {
    }
    void __prli_h() {
        __prlt_address __prli_a;
        prlrt::relay(__prli_a, 6, __prlt_uint32(1));
        prlrt::relay(__prli_a, 2);
    }
    void __prli_ff(__prlt_array<__prlt_token> __prli_n) {
        __prlt_address __prli_a;
        __prlt_array<__prlt_token> __prli_n1;
        prlrt::relay(__prli_a, 7, __prli_n1);
    }
    void __prli___relaylambda_3() {
        __prlt_address __prli_a;
        prlrt::relay(__prli_a, 5);
    }
    void __prli___relaylambda_4() {
    }
};

extern "C" {
    API_EXPORT uint32_t Contract_MyDApp_Dev_6_TransactionCallEntry(void *pContractInstance, uint32_t functionId, uint8_t *args, uint32_t args_size) {
        try {
            switch (functionId){
            case 0:
            {
                if (args_size != 0) return uint32_t(prlrt::ExecutionError::ArgumentDeserializationFailure);
                ((__prlt_Dev *)pContractInstance)->__prli_address_pulse_yield();
                break;
            }
            case 1:
            {
                if (args_size != 0) return uint32_t(prlrt::ExecutionError::ArgumentDeserializationFailure);
                ((__prlt_Dev *)pContractInstance)->__prli_pulse_yield();
                break;
            }
            case 2:
            {
                if (args_size != 0) return uint32_t(prlrt::ExecutionError::ArgumentDeserializationFailure);
                ((__prlt_Dev *)pContractInstance)->__prli_g();
                break;
            }
            case 3:
            {
                if (args_size != 0) return uint32_t(prlrt::ExecutionError::ArgumentDeserializationFailure);
                ((__prlt_Dev *)pContractInstance)->__prli___relaylambda_3();
                break;
            }
            case 4:
            {
                if (args_size != 0) return uint32_t(prlrt::ExecutionError::ArgumentDeserializationFailure);
                ((__prlt_Dev *)pContractInstance)->__prli___relaylambda_4();
                break;
            }
            case 5:
            {
                if (args_size != 0) return uint32_t(prlrt::ExecutionError::ArgumentDeserializationFailure);
                __prlt_uint16 ret = ((__prlt_Dev *)pContractInstance)->__prli_f();
                prlrt::report_return_value("uint16", ret);
                break;
            }
            case 6:
            {
                __prlt_uint32 arg0;
                if (!arg0.map_from_serialized_data(args, args_size, true)) return uint32_t(prlrt::ExecutionError::ArgumentDeserializationFailure);
                if (args_size != 0) return uint32_t(prlrt::ExecutionError::ArgumentDeserializationFailure);
                ((__prlt_Dev *)pContractInstance)->__prli_g(arg0);
                break;
            }
            case 7:
            {
                __prlt_array<__prlt_token> arg0;
                if (!arg0.map_from_serialized_data(args, args_size, true)) return uint32_t(prlrt::ExecutionError::ArgumentDeserializationFailure);
                if (args_size != 0) return uint32_t(prlrt::ExecutionError::ArgumentDeserializationFailure);
                ((__prlt_Dev *)pContractInstance)->__prli_ff(arg0);
                break;
            }
            default: return uint32_t(prlrt::ExecutionError::FunctionNotFound);
            }
        } catch (prlrt::preda_exception &e) {
            return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(e.type()) << 8);
        }
        
        return uint32_t(prlrt::ExecutionError::NoError);
    }
    
    API_EXPORT uint32_t Contract_MyDApp_Dev_6_ContractCallEntry(void *pContractInstance, uint32_t functionId, const void **ptrs, uint32_t numPtrs) {
        return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExceptionType::CrossCallFunctionNotFound) << 8);
    }
    
    API_EXPORT void Contract_MyDApp_Dev_6_InitTables(uint64_t *importedContractIds, uint32_t *issuesAssetIds) {
        __prli___contract_slot = importedContractIds;
        __prli___asset_slot = issuesAssetIds;
    }
    
    API_EXPORT void* Contract_MyDApp_Dev_6_CreateInstance(prlrt::IRuntimeInterface *pInterface) {
        prlrt::g_executionEngineInterface = pInterface;
        return new __prlt_Dev;
    }
    
    API_EXPORT void Contract_MyDApp_Dev_6_DestroyInstance(void *pContract) {
        delete (__prlt_Dev *)pContract;
    }
    
    API_EXPORT bool Contract_MyDApp_Dev_6_MapContractContextToInstance(void *pInstance, prlrt::ContractContextType type, uint8_t *buffer, uint32_t bufferSize) {
        __prlt_Dev *pClassInst = (__prlt_Dev *)pInstance;
        uint8_t *read_ptr = buffer;
        prlrt::serialize_size_type readbuf_size = prlrt::serialize_size_type(bufferSize);
        
        switch (type) {
        case prlrt::ContractContextType::Global:
            if (readbuf_size != 0) return false;
            return true;
        case prlrt::ContractContextType::PerShard:
            if (readbuf_size != 0) return false;
            return true;
        case prlrt::ContractContextType::PerAddress:
            if (!pClassInst->__prli_m_m.map_from_serialized_data(read_ptr, readbuf_size, false)) return false;
            if (!pClassInst->__prli_m_ai.map_from_serialized_data(read_ptr, readbuf_size, false)) return false;
            if (readbuf_size != 0) return false;
            return true;
        }
        
        return false;
    }
    
    API_EXPORT uint32_t Contract_MyDApp_Dev_6_GetContractContextSerializeSize(void *pInstance, prlrt::ContractContextType type) {
        __prlt_Dev *pClassInst = (__prlt_Dev *)pInstance;
        uint32_t ret = 0;
        
        switch (type) {
        case prlrt::ContractContextType::Global:
            return ret;
        case prlrt::ContractContextType::PerShard:
            return ret;
        case prlrt::ContractContextType::PerAddress:
            ret += pClassInst->__prli_m_m.get_serialize_size();
            ret += pClassInst->__prli_m_ai.get_serialize_size();
            return ret;
        }
        
        return ret;
    }
    
    API_EXPORT uint32_t Contract_MyDApp_Dev_6_SerializeOutContractContext(void *pInstance, prlrt::ContractContextType type, uint8_t *buffer) {
        __prlt_Dev *pClassInst = (__prlt_Dev *)pInstance;
        uint8_t *write_ptr = buffer;
        
        try {
            switch (type) {
            case prlrt::ContractContextType::Global:
                break;
            case prlrt::ContractContextType::PerShard:
                break;
            case prlrt::ContractContextType::PerAddress:
                pClassInst->__prli_m_m.serialize_out(write_ptr, false);  write_ptr += pClassInst->__prli_m_m.get_serialize_size();
                pClassInst->__prli_m_ai.serialize_out(write_ptr, false);  write_ptr += pClassInst->__prli_m_ai.get_serialize_size();
                break;
            default: return uint32_t(prlrt::ExecutionError::SerializeOutUnknownContextClass);
            }
        } catch (prlrt::preda_exception &e) {
            return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(e.type()) << 8);
        }
        
        return uint32_t(prlrt::ExecutionError::NoError);
    }
}

}

