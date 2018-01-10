/*
-----    -------
----   ## ------
---   ##   -----
---   #    -----
---        -----
----       -----
------    ------
-----   --------
----     -------
----      ------
----       -----
----       -----
----       -----
----      ------
---       ------
---       ------
---       ------
---       ------
---#       -----
---##    #  ----
-- ##    #  ----
--##    ##  ----
- ##    ##   ---
  ##    ###  ---
  #     ###  ---
-       ###  ---
---     ####  --
----#   ####  --
----########----
----########----
----####-###----
----####-###----
----###-###-----
---####-###-----
---###--###-----
--###---###-----
--##----###-----
--##-----##-----
-##------##-----
-##-------##----
###-------##----
####------###---
#-##------####--
#--###----#-####
*/



const unsigned char PROGMEM idle1[] = {
// width, height,
16, 44,
0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x06,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xe0,0xfc,0x18,0x00,0x00,0x00,0xe0,0xf8,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x00,0xf8,0xf0,0xf0,0xf0,0x3f,0xff,0xff,0xfc,0x00,0x00,0x00,0x00,
0x00,0xc0,0xf8,0x3e,0x0f,0x07,0x03,0x00,0x1f,0x7f,0xff,0x80,0x00,0x00,0x00,0x00,
0x0f,0x03,0x07,0x0e,0x08,0x08,0x00,0x00,0x00,0x00,0x0f,0x07,0x0e,0x0c,0x08,0x08
};


const unsigned char PROGMEM idle1_mask[] = {
0x00,0x00,0x00,0x1c,0x3e,0xbf,0xff,0xff,0x7f,0x7e,0x3c,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xc0,0xff,0xff,0xff,0xff,0xff,0xfe,0x1c,0x00,0x00,0x00,0x00,0x00,
0x80,0xc0,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xf8,0xc0,0x00,0x00,0x00,
0x01,0x03,0x03,0x07,0xff,0xff,0xff,0xff,0x3f,0xff,0xff,0xff,0x0f,0x0c,0x00,0x00,
0x00,0xc0,0xf8,0x3e,0x0f,0x07,0x03,0x00,0x1f,0x7f,0xff,0x80,0x00,0x00,0x00,0x00,
0x0f,0x03,0x07,0x0e,0x08,0x08,0x00,0x00,0x00,0x00,0x0f,0x07,0x0e,0x0c,0x08,0x08
};



const unsigned char PROGMEM idle1_plus_mask[] = {
// width, height,
16, 44,
0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x1c,0x00, 0x3e,0x00, 0xbf,0x0c, 0xff,0x06, 0xff,0x02, 0x7f,0x00, 0x7e,0x00, 0x3c,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,
0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0xc0,0x00, 0xff,0x00, 0xff,0x00, 0xff,0x00, 0xff,0x00, 0xff,0x00, 0xfe,0x00, 0x1c,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,
0x00, 0x80,0x00, 0xc0,0xe0, 0xf0,0xfc, 0xff,0x18, 0xff,0x00, 0xff,0x00, 0xff,0x00, 0xff,0xe0, 0xff,0xf8, 0xff,0x80, 0xfc,0x00, 0xf8,0x00, 0xc0,0x00, 0x00,0x00, 0x00,0x00, 0x00,
0x00, 0x01,0x00, 0x03,0x01, 0x03,0x00, 0x07,0xf8, 0xff,0xf0, 0xff,0xf0, 0xff,0xf0, 0xff,0x3f, 0x3f,0xff, 0xff,0xff, 0xff,0xfc, 0xff,0x00, 0x0f,0x00, 0x0c,0x00, 0x00,0x00, 0x00,
0x00, 0x00,0xc0, 0xc0,0xf8, 0xf8,0x3e, 0x3e,0x0f, 0x0f,0x07, 0x07,0x03, 0x03,0x00, 0x00,0x1f, 0x1f,0x7f, 0x7f,0xff, 0xff,0x80, 0x80,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,
0x0f, 0x0f,0x03, 0x03,0x07, 0x07,0x0e, 0x0e,0x08, 0x08,0x08, 0x08,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x0f, 0x0f,0x07, 0x07,0x0e, 0x0e,0x0c, 0x0c,0x08, 0x08,0x08, 0x08
};


const uint8_t PROGMEM idle1_comp_w[] = {
0x0f,0x2f,0x30,0xb6,0xdc,0x06,0xa5,0xa9,0xad,0x9a,0x5f,0x29,0xa9,0xc3,0x5b,0x8c,
0xd2,0x39,0xe7,0x1c,0xd3,0x7c,0x5b,0x6c,0xad,0x64,0x72,0xe7,0x94,0x9c,0x4d,0x2a,
0x9d,0xd7,0xf1,0x3b,0xb7,0x55,0x56,0xe9,0x74,0x38,0x72,0x4e,0x59,0x65,0xd7,0xe9,
0x1c
}; // 49b vs 96b uncompressed
const uint8_t PROGMEM idle1_comp_b[] = {
0x0f,0x2f,0x98,0x95,0x93,0xdb,0xd4,0x72,0x9b,0xdc,0x2a,0x87,0x47,0x4c,0xa5,0x57,
0x18,0xcb,0xee,0x52,0x5b,0x35,0xbf,0x52,0x5a,0x3a,0x69,0xe7,0x4d,0xaf,0xb3,0x4a,
0x2a,0xe9,0x9c,0x73,0x8e,0x7b,0xeb,0xec,0x70,0x22
}; // 42b vs 96b uncompressed
const uint8_t PROGMEM idle1_comp_a[] = {
0x0f,0x2f,0x98,0x95,0x93,0xdb,0x78,0xb7,0xca,0xe1,0x11,0x53,0xe9,0x15,0xc6,0xb2,
0x3b,0xdc,0x6d,0x95,0xb4,0xf3,0xa6,0xb7,0x5b,0x25,0xb1,0x34,0xb7,0x1d,0x43,0x2b,
0x99,0xdc,0x39,0x25,0x67,0x93,0x4a,0xe7,0x75,0xfc,0xce,0x6d,0x95,0x55,0x3a,0x1d,
0x8e,0x9c,0x53,0x56,0xd9,0x75,0x3a,0x07
}; // 56b vs 96b uncompressed
