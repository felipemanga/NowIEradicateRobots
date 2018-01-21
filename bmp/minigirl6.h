/*
-----######-----
----#      #----
---#        #---
---#        #---
---#        #---
---#        #---
----#      #----
----###  ###----
---##      ##---
--## #    # #---
--# ##    ##----
---##      #----
----#      #----
-----#    #-----
------#####-----
---------##-----
*/



const unsigned char PROGMEM minigirl6[] = {
// width, height,
16, 16,
0x00,0x00,0x00,0x3c,0xc2,0x81,0x81,0x01,0x01,0x81,0x81,0xc2,0x3c,0x00,0x00,0x00,
0x00,0x00,0x06,0x0b,0x1d,0x26,0x40,0x40,0x40,0xc0,0xe6,0x1d,0x03,0x00,0x00,0x00
};


const unsigned char PROGMEM minigirl6_mask[] = {
0x00,0x00,0x00,0x3c,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x3c,0x00,0x00,0x00,
0x00,0x00,0x06,0x0f,0x1f,0x3f,0x7f,0x7f,0x7f,0xff,0xff,0x1f,0x03,0x00,0x00,0x00
};



const unsigned char PROGMEM minigirl6_plus_mask[] = {
// width, height,
16, 16,
0x00, 0x00,0x00, 0x00,0x00, 0x00,0x3c, 0x3c,0xc2, 0xfe,0x81, 0xff,0x81, 0xff,0x01, 0xff,0x01, 0xff,0x81, 0xff,0x81, 0xff,0xc2, 0xfe,0x3c, 0x3c,0x00, 0x00,0x00, 0x00,0x00, 0x00,
0x00, 0x00,0x00, 0x00,0x06, 0x06,0x0b, 0x0f,0x1d, 0x1f,0x26, 0x3f,0x40, 0x7f,0x40, 0x7f,0x40, 0x7f,0xc0, 0xff,0xe6, 0xff,0x1d, 0x1f,0x03, 0x03,0x00, 0x00,0x00, 0x00,0x00, 0x00
};


const uint8_t PROGMEM minigirl6_comp_w[] = {
0x0f,0x0f,0x98,0x9d,0xca,0x29,0xbb,0x5d,0xa7,0xb3,0xdb,0xca,0xbd,0x43,0xd5,0xf2,
0x72,0xa5,0xdc,0xe7,0xd3,0xe9,0xf4,0xbd,0x4b,0xa9,0xd9,0x01
}; // 28b vs 32b uncompressed
const uint8_t PROGMEM minigirl6_comp_b[] = {
0x0f,0x0f,0x30,0xe4,0x94,0xdd,0xae,0xd3,0xd9,0xad,0x72,0xb8,0xcb,0x66,0x7b,0x65,
0xb7,0xdb,0xed,0xbd,0x0b,0x4b
}; // 22b vs 32b uncompressed
const uint8_t PROGMEM minigirl6_comp_a[] = {
0x0f,0x0f,0x98,0x9d,0x42,0x5b,0x7a,0x87,0xaa,0xa5,0x73,0x52,0xd9,0x75,0x3a,0x1d,
0xa9,0x9a,0x1d
}; // 19b vs 32b uncompressed