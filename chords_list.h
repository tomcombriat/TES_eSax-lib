
// TODO: make a structure?


#define N_CHORD 12


const unsigned int chord0_N = 2;
const int chord0_notes[chord0_N] = {0, 7};
const char chord0_name = 'P';
const String chord0_long_name = "Power";

const unsigned int chord1_N = 4;
const int chord1_notes[chord1_N] = {0, 7, 9, 12};
const char chord1_name = '7';
const String chord1_long_name = "7th";

const unsigned int chord2_N = 4;
const int chord2_notes[chord2_N] = {0, 7, 12, -12};
const char chord2_name = 'B';
const String chord2_long_name = "Full B";

const unsigned int chord3_N = 3;
const int chord3_notes[chord3_N] = {0, 3, 7};
const char chord3_name = 'm';
const String chord3_long_name = "min";

const unsigned int chord4_N = 3;
const int chord4_notes[chord4_N] = {0, 4, 7};
const char chord4_name = 'M';
const String chord4_long_name = "Maj";

const unsigned int chord5_N = 4;
const int chord5_notes[chord5_N] = {0, 4, 7, 11};
const char chord5_name = '7';
const String chord5_long_name = "Maj7";

const unsigned int chord6_N = 4;
const int chord6_notes[chord6_N] = {0, 4, 7, 10};
const char chord6_name = '7';
const String chord6_long_name = "dom7";

const unsigned int chord7_N = 4;
const int chord7_notes[chord7_N] = {0, 3, 7, 10};
const char chord7_name = '7';
const String chord7_long_name = "m7";


const unsigned int chord8_N = 3;
const int chord8_notes[chord8_N] = {0, 2, 7};
const char chord8_name = '2';
const String chord8_long_name = "sus2";


const unsigned int chord9_N = 3;
const int chord9_notes[chord9_N] = {0, 5, 7};
const char chord9_name = '4';
const String chord9_long_name = "sus4";

const unsigned int chord10_N = 3;
const int chord10_notes[chord10_N] = {0, 4, 9};
const char chord10_name = '6';
const String chord10_long_name = "maj6no5";

const unsigned int chord11_N = 2;
const int chord11_notes[chord11_N] = {0, 5};
const char chord11_name = '5';
const String chord11_long_name = "d5";



const int * chord_notes[N_CHORD] = {chord0_notes, chord1_notes, chord2_notes, chord3_notes, chord4_notes, chord5_notes, chord6_notes, chord7_notes, chord8_notes, chord9_notes, chord10_notes, chord11_notes};
const char chord_names[N_CHORD] = {chord0_name, chord1_name, chord2_name, chord3_name, chord4_name, chord5_name, chord6_name, chord7_name, chord8_name, chord9_name, chord10_name, chord11_name};
const int chord_N[N_CHORD] = {chord0_N, chord1_N, chord2_N, chord3_N, chord4_N, chord5_N, chord6_N, chord7_N, chord8_N, chord9_N, chord10_N, chord11_N};
const String * chord_long_names[N_CHORD] = {&chord0_long_name, &chord1_long_name, &chord2_long_name, &chord3_long_name, &chord4_long_name, &chord5_long_name, &chord6_long_name, &chord7_long_name, &chord8_long_name, &chord9_long_name, &chord10_long_name, &chord11_long_name};


