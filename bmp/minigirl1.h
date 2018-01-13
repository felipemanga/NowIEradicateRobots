/*
-----######-----
----#      #----
---#  ####  #---
---# #    # #---
---#        #---
---#        #---
----#      #----
----###  ###----
---##      ##---
--## #    # ##--
--# ##    ## #--
----#      #----
----#      #----
-----#    #-----
-----######-----
-----##--##-----
*/



const unsigned char PROGMEM minigirl1[] = {
// width, height,
16, 16,
0x00,0x00,0x00,0x3c,0xc2,0x89,0x85,0x05,0x05,0x85,0x89,0xc2,0x3c,0x00,0x00,0x00,
0x00,0x00,0x06,0x03,0x1d,0xe6,0xc0,0x40,0x40,0xc0,0xe6,0x1d,0x03,0x06,0x00,0x00
};


const unsigned char PROGMEM minigirl1_mask[] = {
0x00,0x00,0x00,0x3c,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x3c,0x00,0x00,0x00,
0x00,0x00,0x06,0x07,0x1f,0xff,0xff,0x7f,0x7f,0xff,0xff,0x1f,0x07,0x06,0x00,0x00
};



const unsigned char PROGMEM minigirl1_plus_mask[] = {
// width, height,
16, 16,
0x00, 0x00,0x00, 0x00,0x00, 0x00,0x3c, 0x3c,0xc2, 0xfe,0x89, 0xff,0x85, 0xff,0x05, 0xff,0x05, 0xff,0x85, 0xff,0x89, 0xff,0xc2, 0xfe,0x3c, 0x3c,0x00, 0x00,0x00, 0x00,0x00, 0x00,
0x00, 0x00,0x00, 0x00,0x06, 0x06,0x03, 0x07,0x1d, 0x1f,0xe6, 0xff,0xc0, 0xff,0x40, 0x7f,0x40, 0x7f,0xc0, 0xff,0xe6, 0xff,0x1d, 0x1f,0x03, 0x07,0x06, 0x06,0x00, 0x00,0x00, 0x00
};


const uint8_t PROGMEM minigirl1_comp_w[] = {
0x0f,0x0f,0x98,0x9d,0xca,0xa9,0x53,0x97,0xbb,0x64,0x25,0x2b,0xf7,0xa9,0xca,0xbd,
0x43,0xd5,0x72,0x5b,0xca,0xbd,0xb2,0xdb,0x74,0xfa,0xde,0xa5,0xd4,0x7a,0x52
}; // 31b vs 32b uncompressed
const uint8_t PROGMEM minigirl1_comp_b[] = {
0x0f,0x0f,0x30,0xe4,0xd4,0xa9,0xcb,0x5d,0xb2,0x92,0x95,0xfb,0x94,0x72,0xb8,0xcb,
0x66,0x7b,0x65,0xb7,0xdb,0xed,0xbd,0xcb,0x47,0x0e
}; // 26b vs 32b uncompressed
const uint8_t PROGMEM minigirl1_comp_a[] = {
0x0f,0x0f,0x98,0x9d,0x42,0x5b,0x7a,0x87,0xaa,0xa5,0x92,0x52,0xd1,0xa6,0x23,0x55,
0xca,0x4e,0x0a
}; // 19b vs 32b uncompressed