  #include "bytemicrocircuit.hpp"                                                 
  #include "byte_splitter.hpp"                                                    
  #include "byte_maker.hpp"                                                       
  #include "nor.hpp"                                                             
  #ifndef BYTE_NOR_H                                                             
  #define BYTE_NOR_H                                                             
  namespace Virtual{                                                              
                                                                                  
  class ByteNor : public byteMicroCircuit<0,2,0,1,11> {                          
    public:                                                                       
      ByteNor(ptr8_t inA=ground8, ptr8_t inB=ground8);                           
      void rewire_input();                                                        
      static const std::string gate_name;                                         
  };                                                                              
                                                                                  
  } //namespace Virtual                                                           
                                                                                  
  #endif 
