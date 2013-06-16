#include "gtest/gtest.h"

#include "fg/variable.h"
#include "fg/variablescanner.h"

double print_variable(char * buf, void * ppara){
  Variable * pvar = reinterpret_cast<Variable*>(buf);
  bool a = pvar->vid >= 0 && pvar->vid <= 429451;
  EXPECT_EQ(a, true);
  EXPECT_EQ(pvar->type, 'C');
  EXPECT_EQ(pvar->lower, 1);
  EXPECT_EQ(pvar->upper, 50);
  EXPECT_EQ(pvar->nfactor, 3);
  a = *pvar->get_i_value(0) >= 1 && *pvar->get_i_value(0) <= 50;
  EXPECT_EQ(a, true);
}

double update_variable(char * buf, void * ppara){
  Variable * pvar = reinterpret_cast<Variable*>(buf);
  for(int i=0;i<3;i++){
    *pvar->get_i_fid(i) = (long) i*4+0;
    *pvar->get_i_f_group(i) = i*4+1;
    *pvar->get_i_f_pos(i) = i*4+2;
    *pvar->get_i_f_aux(i) = i*4+3;   
    
  }
  *pvar->get_i_value(0) = 12.5;
}

double print_variable2(char * buf, void * ppara){
  Variable * pvar = reinterpret_cast<Variable*>(buf);
  bool a = pvar->vid >= 0 && pvar->vid <= 429451;
  EXPECT_EQ(a, true);
  EXPECT_EQ(pvar->type, 'C');
  EXPECT_EQ(pvar->lower, 1);
  EXPECT_EQ(pvar->upper, 50);
  EXPECT_EQ(pvar->nfactor, 3);
  for(int i=0;i<3;i++){
    EXPECT_EQ(*pvar->get_i_fid(i) ,i*4+0);
    EXPECT_EQ(*pvar->get_i_f_group(i) ,i*4+1);
    EXPECT_EQ(*pvar->get_i_f_pos(i) ,i*4+2);
    EXPECT_EQ(*pvar->get_i_f_aux(i) ,i*4+3);    
  }
  EXPECT_EQ(*pvar->get_i_value(0), 12.5);
}



TEST (VARIABLESCANNER_TEST, LOAD){
  
  VariableScanner<Driver_FILE> vs(409600, "/tmp/testvariablescanner");
  long nvariable = vs.load("/tmp/deepdive/variables.tsv");
  EXPECT_EQ(nvariable, 429451);
  
  vs.scan(&print_variable);
  vs.scan(&update_variable);
  vs.scan(&print_variable2);
    
  //vs.scan_prefetch(&print_variable);
  //vs.scan_prefetch(&update_variable);
  //vs.scan_prefetch(&print_variable2);
}