#include <Nextion.h>
#include <EEPROM.h>
#include "Arduino.h"

SoftwareSerial HMISerial(10,11);

// Component Declarations

NexPage homepage = NexPage(0, 0, "homepage");
  NexButton bn_settings = NexButton(0, 1, "bn_settings");
  NexButton bn_results = NexButton(0, 2, "bn_results");
  NexButton bn_mail = NexButton(0, 3, "bn_mail");
  NexButton bn_vote = NexButton(0, 4, "bn_vote");
  NexButton bn_no_vote = NexButton(0, 5, "bn_no_vote");
  NexButton bn_no_vote1 = NexButton(0, 6, "bn_no_vote1");
  
  
NexPage courses = NexPage(1, 0, "courses");
 NexText text_mecht = NexText(1, 2, "text_mecht");
 NexText text_eee = NexText(1, 3, "text_eee");
 NexText text_civil = NexText(1, 4, "text_civil");
 NexText text_tie = NexText(1, 5, "text_tie");
 NexText text_marine = NexText(1, 6, "text_marine");
 NexText text_gegis = NexText(1, 7, "text_gegis");
 NexText text_mech = NexText(1, 8, "text_mech");
 NexText text_abe = NexText(1, 9, "text_abe");
 NexText text_cancel_1 = NexText(1, 10, "text_cancel_1");

NexPage mechatronics = NexPage(2, 0, "mechatronics");
 NexText text_cancel_2 = NexText(2, 1, "text_cancel_2");
 NexText text_linda = NexText(2, 3, "text_linda");
 NexText text_magdeline = NexText(2, 4, "text_magdeline");
 NexText text_kelvin = NexText(2, 5, "text_kelvin");
 
NexPage eee_ece = NexPage(3, 0, "eee_ece");
 NexText text_cancel_3 = NexText(3, 1, "text_cancel_3");
 NexText text_allan = NexText(3, 3, "text_allan");
 NexText text_gitahi = NexText(3, 4, "text_gitahi");
 NexText text_koi = NexText(3, 5, "text_koi");

NexPage civil_eng = NexPage(4, 0, "civil_eng");
 NexText text_cancel_4 = NexText(4, 1, "text_cancel_4");
 NexText text_joy = NexText(4, 3, "text_joy");
 NexText text_odhiambo = NexText(4, 4, "text_odhiambo");
 NexText text_ian = NexText(4, 5, "text_ian");


NexPage tie = NexPage(5, 0, "tie");
 NexText text_cancel_5 = NexText(5, 1, "text_cancel_5");
 NexText text_kibali = NexText(5, 3, "text_kibali");
 NexText text_miriam = NexText(5, 4, "text_miriam");

NexPage abe = NexPage(6, 0, "abe");
 NexText text_cancel_6 = NexText(6, 1, "text_cancel_6");
 NexText text_moses = NexText(6, 3, "text_moses");
 NexText text_dan = NexText(6, 4, "text_dan");

NexPage mechanical = NexPage(7, 0, "mechanical");
 NexText text_cancel_7 = NexText(7, 1, "text_cancel_7");
 NexText text_nashon = NexText(7, 3, "text_nashon");

NexPage gegis = NexPage(8, 0, "gegis");
 NexText text_cancel_8 = NexText(8, 1, "text_cancel_8");
 NexText text_dolphine = NexText(8, 3, "text_dolphine");

NexPage marine_mining = NexPage(9, 0, "marine_mining");
 NexText text_cancel_9 = NexText(9, 1, "text_cancel_9");
 NexText text_reja = NexText(9, 3, "text_reja");

NexPage sec_gen = NexPage(10, 0, "sec_gen");
 NexText text_cancel_10 = NexText(10, 1, "text_cancel_10");
 NexText text_lorraine = NexText(10, 3, "text_lorraine");

NexPage treasurer = NexPage(11, 0, "treasurer");
 NexText text_cancel_11 = NexText(11, 1, "text_cancel_11");
 NexText text_noel = NexText(11, 3, "text_noel");

NexPage vice_president = NexPage(12, 0, "vice_president");
 NexText text_cancel_12 = NexText(12, 1, "text_cancel_12");
 NexText text_hampton = NexText(12, 3, "text_hampton");

NexPage president = NexPage(13, 0, "president");
 NexText text_cancel_13 = NexText(13, 1, "text_cancel_13");
 NexText text_brenda = NexText(13, 3, "text_brenda");

NexPage thanks = NexPage(14, 0, "thanks");
 NexText text_prep = NexText(14, 2, "text_prep");

NexPage password = NexPage(15, 0, "password");
  NexButton bn_sigma = NexButton(15, 2, "bn_sigma");
  NexButton bn_gamma = NexButton(15, 3, "bn_gamma");
  NexButton bn_psi = NexButton(15, 4, "bn_psi");
  NexButton bn_phi = NexButton(15, 5, "bn_phi");
  NexButton bn_alpha = NexButton(15, 6, "bn_alpha");
  NexButton bn_epsilom = NexButton(15, 7, "bn_epsilom");
  NexButton bn_theta = NexButton(15, 8, "bn_theta");
  NexButton bn_nought = NexButton(15, 9, "bn_nought");
  NexText text_cancel_15 = NexText(15, 10, "text_cancel_15");
  NexText text_pass = NexText(15, 11, "text_pass");

NexPage results1 = NexPage(16, 0, "results1");
  NexText text_cancel_16 = NexText(16, 2, "text_cancel_16");
  NexText text_linda_r = NexText(16, 10, "text_linda_r");
  NexText text_kelvin_r = NexText(16, 11, "text_kelvin_r");
  NexText t_magdeline_r = NexText(16, 12, "t_magdeline_r");
  NexText text_allan_r = NexText(16, 16, "text_allan_r");
  NexText text_gitahi_r = NexText(16, 17, "text_gitahi_r");
  NexText text_koi_r = NexText(16, 18, "text_koi_r");
  NexText text_kendi_r = NexText(16, 22, "text_kendi_r");
  NexText t_odhiambo_r = NexText(16, 23, "t_odhiambo_r");
  NexText text_ian_r = NexText(16, 24, "text_ian_r");
  NexText text_kibali_r = NexText(16, 27, "text_kibali_r");
  NexText text_miriam_r = NexText(16, 28, "text_miriam_r");
  NexButton bn_forward_16 = NexButton(16, 29, "bn_forward_16");  
  
NexPage results2 = NexPage(17, 0, "results2");
  NexText text_cancel_17 = NexText(17, 2, "text_cancel_17");
  NexText text_moses_r = NexText(17, 9, "text_moses_r");
  NexText text_dan_r = NexText(17, 10, "text_dan_r");
  NexText text_nashon_r = NexText(17, 12, "text_nashon_r");
  NexText t_dolphine_r = NexText(17, 14, "t_dolphine_r");
  NexText text_reja_r = NexText(17, 16, "text_reja_r");
  NexButton bn_back_17 = NexButton(17, 17, "bn_back_17");
  NexButton bn_forward_17 = NexButton(17, 18, "bn_forward_17");
  
NexPage results3 = NexPage(18, 0, "results3");
  NexText text_cancel_18 = NexText(18, 2, "text_cancel_18");
  NexText t_lorraine_r = NexText(18, 10, "t_lorraine_r");
  NexText text_noel_r = NexText(18, 11, "text_noel_r");
  NexText text_hampton_r = NexText(18, 12, "text_hampton_r");
  NexText text_brenda_r = NexText(18, 16, "text_brenda_r");
  NexButton bn_back_18 = NexButton(18, 15, "bn_back_18");

NexTouch *nex_listen_list[] =
{
  &homepage,
    &bn_settings,
    &bn_results,
    &bn_mail,
    &bn_vote,
    &bn_no_vote,
    &bn_no_vote1,
  
  &courses,
    &text_mecht,
    &text_eee,
    &text_civil,
    &text_tie,
    &text_marine,
    &text_gegis,
    &text_mech,
    &text_abe,
    &text_cancel_1,
    
  &mechatronics,
    &text_cancel_2,
    &text_linda,
    &text_magdeline,
    &text_kelvin,
    
  &eee_ece,
    &text_cancel_3,
    &text_allan,
    &text_gitahi,
    &text_koi,
    
  &civil_eng,
    &text_cancel_4,
    &text_joy,
    &text_odhiambo,
    &text_ian,
    
  &tie,
    &text_cancel_5,
    &text_kibali,
    &text_miriam,
    
  &abe,
    &text_cancel_6,
    &text_moses,
    &text_dan,
    
  &mechanical,
    &text_cancel_7,
    &text_nashon,
    
  &gegis,
    &text_cancel_8,
    &text_dolphine,
    
  &marine_mining,
    &text_cancel_9,
    &text_reja,
    
  &sec_gen,
    &text_cancel_10,
    &text_lorraine,
    
  &treasurer,
    &text_cancel_11,
    &text_noel,
    
  &vice_president,
    &text_cancel_12,
    &text_hampton,
    
  &president,
    &text_cancel_13,
    &text_brenda,
    
  &thanks,
    &text_prep,
    
  &password,
    &bn_sigma,
    &bn_gamma,
    &bn_psi,
    &bn_phi,
    &bn_alpha,
    &bn_epsilom,
    &bn_theta,
    &bn_nought,
    &text_cancel_15,
    &text_pass,
    
  &results1,
    &text_cancel_16,
    &text_linda_r,
    &text_kelvin_r,
    &t_magdeline_r,
    &text_allan_r,
    &text_gitahi_r,
    &text_koi_r,
    &text_kendi_r,
    &t_odhiambo_r,
    &text_ian_r,
    &text_kibali_r,
    &text_miriam_r,
    &bn_forward_16,
    
  &results2,
    &text_cancel_17,
    &text_moses_r,
    &text_dan_r,
    &text_nashon_r,
    &t_dolphine_r,
    &text_reja_r,
    &bn_back_17,
    &bn_forward_17,

    
  &results3,
    &text_cancel_18,
    &t_lorraine_r,
    &text_noel_r,
    &text_hampton_r,
    &text_brenda_r,
    &bn_back_18,
    
  NULL
};

int linda_results = 0;
int magdeline_results = 0;
int kelvin_results = 0;
int allan_results = 0;
int gitahi_results = 0;
int koi_results = 0;
int joy_results = 0;
int odhiambo_results = 0;
int ian_results = 0;
int kibali_results = 0;
int miriam_results = 0;
int moses_results = 0;
int dan_results = 0;
int nashon_results = 0;
int dolphine_results = 0;
int reja_results = 0;
int lorraine_results = 0;
int noel_results = 0;
int hampton_results = 0;
int brenda_results = 0;


void setup() 
{
  // put your setup code here, to run once:
  nexInit();
  Serial.begin(9600);
  HMISerial.begin(9600);

 Serial.print("Initializing");

//Attach to function
bn_settings.attachPop(bn_settingsPopCallback);
bn_results.attachPop(bn_resultsPopCallback);
bn_mail.attachPop(bn_mailPopCallback);
bn_vote.attachPop(bn_votePopCallback);
//bn_no_vote.attachPop(bn_no_votePopCallback);
//bn_no_vote1.attachPop(bn_no_vote1PopCallback);

text_mecht.attachPop(text_mechtPopCallback);
text_eee.attachPop(text_eeePopCallback);
text_civil.attachPop(text_civilPopCallback);
text_tie.attachPop(text_tiePopCallback);
text_marine.attachPop(text_marinePopCallback);
text_gegis.attachPop(text_gegisPopCallback);
text_mech.attachPop(text_mechPopCallback);
text_abe.attachPop(text_abePopCallback);

text_cancel_1.attachPop(text_cancelPopCallback);
text_cancel_2.attachPop(text_cancelPopCallback);
text_cancel_3.attachPop(text_cancelPopCallback);
text_cancel_4.attachPop(text_cancelPopCallback);
text_cancel_5.attachPop(text_cancelPopCallback);
text_cancel_6.attachPop(text_cancelPopCallback);
text_cancel_7.attachPop(text_cancelPopCallback);
text_cancel_8.attachPop(text_cancelPopCallback);
text_cancel_9.attachPop(text_cancelPopCallback);
text_cancel_10.attachPop(text_cancelPopCallback);
text_cancel_11.attachPop(text_cancelPopCallback);
text_cancel_12.attachPop(text_cancelPopCallback);
text_cancel_13.attachPop(text_cancelPopCallback);
text_cancel_15.attachPop(text_cancelPopCallback);
text_cancel_16.attachPop(text_cancelPopCallback);
text_cancel_17.attachPop(text_cancelPopCallback);
text_cancel_18.attachPop(text_cancelPopCallback);

bn_nought.attachPop(bn_noughtPopCallback);

bn_forward_16.attachPop(bn_forward_16PopCallback);
bn_forward_17.attachPop(bn_forward_17PopCallback);
bn_back_17.attachPop(bn_back_17PopCallback);
bn_back_18.attachPop(bn_back_18PopCallback);

text_linda.attachPop(text_lindaPopCallback);
text_magdeline.attachPop(text_magdelinePopCallback);
text_kelvin.attachPop(text_kelvinPopCallback);
text_allan.attachPop(text_allanPopCallback);
text_gitahi.attachPop(text_gitahiPopCallback);
text_koi.attachPop(text_koiPopCallback);
text_joy.attachPop(text_joyPopCallback);
text_odhiambo.attachPop(text_odhiamboPopCallback);
text_ian.attachPop(text_ianPopCallback);
text_kibali.attachPop(text_kibaliPopCallback);
text_miriam.attachPop(text_miriamPopCallback);
text_moses.attachPop(text_mosesPopCallback);
text_dan.attachPop(text_danPopCallback);
text_nashon.attachPop(text_nashonPopCallback);
text_dolphine.attachPop(text_dolphinePopCallback);
text_reja.attachPop(text_rejaPopCallback);
text_lorraine.attachPop(text_lorrainePopCallback);
text_noel.attachPop(text_noelPopCallback);
text_hampton.attachPop(text_hamptonPopCallback);
text_brenda.attachPop(text_brendaPopCallback);

text_prep.attachPop(text_prepPopCallback);

pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
}

void text_lindaPopCallback(void *ptr)
{
 int results_p = EEPROM.read(11);
 results_p = results_p + 1;
 EEPROM.write(11,results_p);
 sec_gen.show(); 
}
void text_magdelinePopCallback(void *ptr)
{
  int results_p = EEPROM.read(12);
  results_p = results_p + 1;
  EEPROM.write(12,results_p);
  sec_gen.show(); 
}
void text_kelvinPopCallback(void *ptr)
{
  int results_p = EEPROM.read(13);
  results_p = results_p + 1;
  EEPROM.write(13,results_p);
  sec_gen.show(); 
}
void text_allanPopCallback(void *ptr)
{
  int results_p = EEPROM.read(14);
  results_p = results_p + 1;
  EEPROM.write(14,results_p);
  sec_gen.show(); 
}
void text_gitahiPopCallback(void *ptr)
{
  int results_p = EEPROM.read(15);
  results_p = results_p + 1;
  EEPROM.write(15,results_p);
  sec_gen.show(); 
}
void text_koiPopCallback(void *ptr)
{
  int results_p = EEPROM.read(16);
  results_p = results_p + 1;
  EEPROM.write(16,results_p);
  sec_gen.show(); 
}
void text_joyPopCallback(void *ptr)
{
  int results_p = EEPROM.read(17);
  results_p = results_p + 1;
  EEPROM.write(17,results_p);
  sec_gen.show(); 
}
void text_odhiamboPopCallback(void *ptr)
{
  int results_p = EEPROM.read(18);
  results_p = results_p + 1;
  EEPROM.write(18,results_p);
  sec_gen.show(); 
}
void text_ianPopCallback(void *ptr)
{
  int results_p = EEPROM.read(19);
  results_p = results_p + 1;
  EEPROM.write(19,results_p);
  sec_gen.show(); 
}
void text_kibaliPopCallback(void *ptr)
{
  int results_p = EEPROM.read(20);
  results_p = results_p + 1;
  EEPROM.write(20,results_p);
  sec_gen.show(); 
}
void text_miriamPopCallback(void *ptr)
{
  int results_p = EEPROM.read(21);
  results_p = results_p + 1;
  EEPROM.write(21,results_p);
  sec_gen.show(); 
}
void text_mosesPopCallback(void *ptr)
{
  int results_p = EEPROM.read(22);
  results_p = results_p + 1;
  EEPROM.write(22,results_p);
  sec_gen.show(); 
}
void text_danPopCallback(void *ptr)
{
  int results_p = EEPROM.read(23);
  results_p = results_p + 1;
  EEPROM.write(23,results_p);
  sec_gen.show(); 
}
void text_nashonPopCallback(void *ptr)
{
  int results_p = EEPROM.read(24);
  results_p = results_p + 1;
  EEPROM.write(24,results_p);
  sec_gen.show(); 
}
void text_dolphinePopCallback(void *ptr)
{
  int results_p = EEPROM.read(25);
  results_p = results_p + 1;
  EEPROM.write(25,results_p);
  sec_gen.show(); 
}
void text_rejaPopCallback(void *ptr)
{
  int results_p = EEPROM.read(26);
  results_p = results_p + 1;
  EEPROM.write(26,results_p);
  sec_gen.show(); 
}
void text_lorrainePopCallback(void *ptr)
{
  int results_p = EEPROM.read(27);
  results_p = results_p + 1;
  EEPROM.write(27,results_p);
  treasurer.show(); 
}
void text_noelPopCallback(void *ptr)
{
  int results_p = EEPROM.read(28);
  results_p = results_p + 1;
  EEPROM.write(28,results_p);
  vice_president.show(); 
}
void text_hamptonPopCallback(void *ptr)
{
  int results_p = EEPROM.read(29);
  results_p = results_p + 1;
  EEPROM.write(29,results_p);
  president.show(); 
}
void text_brendaPopCallback(void *ptr)
{
  int results_p = EEPROM.read(30);
  results_p = results_p + 1;
  EEPROM.write(30,results_p);
  thanks.show(); 
  digitalWrite(13, HIGH);
}

void text_cancelPopCallback(void *ptr)
{
  Serial.print("Button Pressed");
   homepage.show();
   digitalWrite(12, HIGH);
   delay(1000);
    digitalWrite(12, LOW);
}

void bn_settingsPopCallback(void *ptr)
{
  Serial.print("Button Pressed");
   password.show();
}

void bn_resultsPopCallback(void *ptr)
{
  Serial.print("Button Pressed");
   password.show();
}
void bn_mailPopCallback(void *ptr)
{
  Serial.print("Button Pressed");
   password.show();
}
void bn_votePopCallback(void *ptr)
{
  Serial.print("Button Pressed");
   courses.show();
   digitalWrite(13, LOW);
}

void text_mechtPopCallback(void *ptr)
{
  Serial.print("Button Pressed");
  mechatronics.show();
}

void text_eeePopCallback(void *ptr)
{
  Serial.print("Button Pressed");
  eee_ece.show();
}

void text_civilPopCallback(void *ptr)
{
  Serial.print("Button Pressed");
  civil_eng.show();
}

void text_tiePopCallback(void *ptr)
{
  Serial.print("Button Pressed");
  tie.show();
}

void text_marinePopCallback(void *ptr)
{
  Serial.print("Button Pressed");
  marine_mining.show();
}

void text_gegisPopCallback(void *ptr)
{
  Serial.print("Button Pressed");
  gegis.show();
}

void text_mechPopCallback(void *ptr)
{
  Serial.print("Button Pressed");
  mechanical.show();
}

void text_abePopCallback(void *ptr)
{
  Serial.print("Button Pressed");
  abe.show();
}

char buffer_password[4]={0};
String real_password="123";

boolean array_cmp(char *a, char *b, char len_a, char len_b){
     int n;

     // if their lengths are different, return false
     if (len_a != len_b) return false;

     // test each element to be the same. if not, return false
     for (n=0;n<len_a;n++) if (a[n]!=b[n]) return false;

     //ok, if we have not returned yet, they are equal :)
     return true;
}

void bn_noughtPopCallback(void *ptr)
{
  memset(buffer_password, 0, sizeof(buffer_password));
  text_pass.getText(buffer_password, sizeof(buffer_password));

  char real_password_char[4];
  real_password.toCharArray(real_password_char, 4);

  if (array_cmp(real_password_char,buffer_password,4,4) == true)
  {
    results1.show();
    load_results();              
  }
   else
  {
        sendCommand("text_pass.txt=\"Wrong Pass\"");
        delay(500);
        sendCommand("text_pass.txt=\"\"");
  }
}

char linda_results_char[3]={0};
char magdeline_results_char[3]={0};
char kelvin_results_char[3]={0};
char allan_results_char[3]={0};
char gitahi_results_char[3]={0};
char koi_results_char[3]={0};
char joy_results_char[3]={0};
char odhiambo_results_char[3]={0};
char ian_results_char[3]={0};
char kibali_results_char[3]={0};
char miriam_results_char[3]={0};
char moses_results_char[3]={0};
char dan_results_char[3]={0};
char nashon_results_char[3]={0};
char dolphine_results_char[3]={0};
char reja_results_char[3]={0};
char lorraine_results_char[3]={0};
char noel_results_char[3]={0};
char hampton_results_char[3]={0};
char brenda_results_char[3]={0};


void load_results()
{
 linda_results = EEPROM.read(11);
 sprintf(linda_results_char, "%04i", linda_results);
  
 magdeline_results = EEPROM.read(12);
  sprintf(magdeline_results_char, "%04i", magdeline_results);
  
 kelvin_results = EEPROM.read(13);
  sprintf(kelvin_results_char, "%04i", kelvin_results);
  
 allan_results = EEPROM.read(14);
  sprintf(allan_results_char, "%04i", allan_results);
  
 gitahi_results = EEPROM.read(15);
  sprintf(gitahi_results_char, "%04i", gitahi_results);
   
 koi_results = EEPROM.read(16);
  sprintf(koi_results_char, "%04i", koi_results);
  
 joy_results = EEPROM.read(17);
  sprintf(joy_results_char, "%04i", joy_results);
  
 odhiambo_results = EEPROM.read(18);
  sprintf(odhiambo_results_char, "%04i", odhiambo_results);
   
 ian_results = EEPROM.read(19);
  sprintf(ian_results_char, "%04i", ian_results);
  
 kibali_results = EEPROM.read(20);
  sprintf(kibali_results_char, "%04i", kibali_results);
  
 miriam_results = EEPROM.read(21);
  sprintf(miriam_results_char, "%04i", miriam_results);
    
 moses_results = EEPROM.read(22);
  sprintf(moses_results_char, "%04i", moses_results);
  
 dan_results = EEPROM.read(23);
  sprintf(dan_results_char, "%04i", dan_results);
  
 nashon_results = EEPROM.read(24);
  sprintf(nashon_results_char, "%04i", nashon_results);
  
 dolphine_results = EEPROM.read(25);
  sprintf(dolphine_results_char, "%04i", dolphine_results);
  
 reja_results = EEPROM.read(26);
  sprintf(reja_results_char, "%04i", reja_results);
  
 lorraine_results = EEPROM.read(27);
  sprintf(lorraine_results_char, "%04i", lorraine_results);
  
 noel_results = EEPROM.read(28);
  sprintf(noel_results_char, "%04i", noel_results);
  
 hampton_results = EEPROM.read(29);
  sprintf(hampton_results_char, "%04i", hampton_results);
  
 brenda_results = EEPROM.read(30);
  sprintf(brenda_results_char, "%04i", brenda_results);

 Serial.print("Linda Results: ");
 Serial.println(linda_results);

 Serial.print("Linda Results Char: ");
 Serial.println(linda_results_char);
 
 text_linda_r.setText(linda_results_char);
 text_kelvin_r.setText(kelvin_results_char);
 t_magdeline_r.setText(magdeline_results_char);
 text_allan_r.setText(allan_results_char);
 text_gitahi_r.setText(gitahi_results_char);
 text_koi_r.setText(koi_results_char);
 text_kendi_r.setText(joy_results_char);
 t_odhiambo_r.setText(odhiambo_results_char);
 text_ian_r.setText(ian_results_char);
 text_kibali_r.setText(kibali_results_char);
 text_miriam_r.setText(miriam_results_char);
 text_moses_r.setText(moses_results_char);
 text_dan_r.setText(dan_results_char);
 text_nashon_r.setText(nashon_results_char);
 t_dolphine_r.setText(dolphine_results_char);
 text_reja_r.setText(reja_results_char);
 t_lorraine_r.setText(lorraine_results_char);
 text_noel_r.setText(noel_results_char);
 text_hampton_r.setText(hampton_results_char);
 text_brenda_r.setText(brenda_results_char);
 
 
}

void bn_forward_16PopCallback(void *ptr)
{
  results2.show();
  load_results();
}
void bn_forward_17PopCallback(void *ptr)
{
  results3.show();
  load_results();
}
void bn_back_17PopCallback(void *ptr)
{
  results1.show();
  load_results();
}
void bn_back_18PopCallback(void *ptr)
{
  results2.show();
  load_results();
}
void text_prepPopCallback(void *ptr)
{
  homepage.show();
}

//------------------------------------------------------------------------------------
// End of Functions
//------------------------------------------------------------------------------------

void loop() 
{
  Serial.println("Checking");
  // put your main code here, to run repeatedly:
nexLoop(nex_listen_list);
}


