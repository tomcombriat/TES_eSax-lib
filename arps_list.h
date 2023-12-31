#define N_ARP 11



const int arp0_N = 4;
const float arp0_times[arp0_N] = { 0.0, 0.25, 0.5, 0.75 };
const int arp0_notes[arp0_N] = { 0, 7, 19, 12 };
const char arp0_name = 'C';
const String arp0_long_name = "Classic";

const int arp1_N = 4;
const float arp1_times[arp1_N] = { 0.0, 0.25, 0.5, 0.75 };
const int arp1_notes[arp1_N] = { 0, 4, 7, 4 };
const char arp1_name = 'M';
const String arp1_long_name = "Maj";


const int arp2_N = 4;
const float arp2_times[arp2_N] = { 0.0, 0.25, 0.5, 0.75 };
const int arp2_notes[arp2_N] = { 0, 3, 7, 3 };
const char arp2_name = 'm';
const String arp2_long_name = "min";


const int arp3_N = 3;
const float arp3_times[arp3_N] = { 0.0, 0.5, 0.75 };
const int arp3_notes[arp3_N] = { 0, 7, 12 };
const char arp3_name = 'T';
const String arp3_long_name = "F/o";


const int arp4_N = 8;
const float arp4_times[arp4_N] = { 0.0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875 };
const int arp4_notes[arp4_N] = { 0, -255, 0, -255, 0, -255, 0, -255 };
const char arp4_name = '4';
const String arp4_long_name = "4";

const int arp5_N = 4;
const float arp5_times[arp5_N] = { 0.0, 0.25, 0.5, 0.75 };
const int arp5_notes[arp5_N] = { 0, -255, 0, -255 };
const char arp5_name = '2';
const String arp5_long_name = "2";

const int arp6_N = 2;
const float arp6_times[arp6_N] = { 0.0, 0.5 };
const int arp6_notes[arp6_N] = { 0, -255 };
const char arp6_name = '1';
const String arp6_long_name = "1";

const int arp7_N = 6;
const float arp7_times[arp7_N] = { 0.0, 1. / 6, 1. / 3, 0.5, 2. / 3, 5. / 6 };
const int arp7_notes[arp7_N] = { 0, -255, 0, -255, 0, -255 };
const char arp7_name = '3';
const String arp7_long_name = "3";

const int arp8_N = 4;
const float arp8_times[arp8_N] = { 0.0, 0.25, 0.5, 0.75 };
const int arp8_notes[arp8_N] = { 0, 7, -5, 12 };
const char arp8_name = 'F';
const String arp8_long_name = "Fifth";

const int arp9_N = 15;
const float arp9_times[arp9_N] = { 0.0, 0.15, 0.25, 0.4, 0.5, 0.65, 0.75, 1., 1.15, 1.25, 1.40, 1.50, 1.65, 1.75, 1.9 };
const int arp9_notes[arp9_N] = { 0, -255, 0, -255, 0, -255, 0, 3, -255, 2, -255, -5, -255, -2, -255 };
const char arp9_name = 'S';
const String arp9_long_name = "Amb";

const int arp10_N = 8;
const float arp10_times[arp10_N] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75 };
const int arp10_notes[arp10_N] = { 0, 7, 3, 10, 0, 7, 5, 10 };
const char arp10_name = 'P';
const String arp10_long_name = "Penta";



const float* arp_times[N_ARP] = { arp0_times, arp1_times, arp2_times, arp3_times, arp4_times, arp7_times, arp5_times, arp6_times, arp8_times, arp9_times, arp10_times };
const int* arp_notes[N_ARP] = { arp0_notes, arp1_notes, arp2_notes, arp3_notes, arp4_notes, arp7_notes, arp5_notes, arp6_notes, arp8_notes, arp9_notes, arp10_notes };
const char arp_name[N_ARP] = { arp0_name, arp1_name, arp2_name, arp3_name, arp4_name, arp7_name, arp5_name, arp6_name, arp8_name, arp9_name, arp10_name };
const int arp_N[N_ARP] = { arp0_N, arp1_N, arp2_N, arp3_N, arp4_N, arp7_N, arp5_N, arp6_N, arp8_N, arp9_N, arp10_N };
const String* arp_long_names[N_ARP] = { &arp0_long_name, &arp1_long_name, &arp2_long_name, &arp3_long_name, &arp4_long_name, &arp7_long_name, &arp5_long_name, &arp6_long_name, &arp8_long_name, &arp9_long_name, &arp10_long_name };
