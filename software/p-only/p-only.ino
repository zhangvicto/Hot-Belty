//NOTES: 
//P-Only Controller
//CO = CObias + Kc*e(t)
//CObias = controller bias or null value
//Kc = controller gain, a tuning parameter
//e(t) = controller error = SP – PV
//SP = set point
//PV = measured process variable
//https://controlguru.com/the-p-only-control-algorithm/
//https://controlguru.com/design-and-tuning-recipe-must-consider-nonlinear-process-behavior/

const int coBias = 20;
int co;
int kc = 2.5;
int SP;
int PV;
int e_t;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
