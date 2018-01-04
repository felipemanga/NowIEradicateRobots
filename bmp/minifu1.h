/*
-------  -------
--- --    -- ---
  - -      - -  
    -      -    
                
-              -
--            --
-    -    -    -
-   ---  ---   -
-  -  -  -  -  -
-------  -------
-------  -------
-------  -------
-------  -------
-------  -------
-------  -------
*/



const unsigned char PROGMEM minifu1[] = {
// width, height,
16, 16,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


const unsigned char PROGMEM minifu1_mask[] = {
0x1c,0xbc,0xf8,0xfe,0xf0,0x7c,0xfe,0xff,0xff,0xfe,0x7c,0xf0,0xfe,0xf8,0xbc,0x1c,
0x00,0x03,0x03,0x01,0x02,0x02,0x00,0xff,0xff,0x00,0x02,0x02,0x01,0x03,0x03,0x00
};



const unsigned char PROGMEM minifu1_plus_mask[] = {
// width, height,
16, 16,
0x00, 0x1c,0x00, 0xbc,0x00, 0xf8,0x00, 0xfe,0x00, 0xf0,0x00, 0x7c,0x00, 0xfe,0x00, 0xff,0x00, 0xff,0x00, 0xfe,0x00, 0x7c,0x00, 0xf0,0x00, 0xfe,0x00, 0xf8,0x00, 0xbc,0x00, 0x1c,
0x00, 0x00,0x00, 0x03,0x00, 0x03,0x00, 0x01,0x00, 0x02,0x00, 0x02,0x00, 0x00,0x00, 0xff,0x00, 0xff,0x00, 0x00,0x00, 0x02,0x00, 0x02,0x00, 0x01,0x00, 0x03,0x00, 0x03,0x00, 0x00
};


const uint8_t PROGMEM minifu1_comp_w[] = {
0x0f,0x0f,0xe0,0x3f
}; // 4b vs 32b uncompressed
const uint8_t PROGMEM minifu1_comp_b[] = {
0x0f,0x0f,0x56,0xd2,0x95,0x92,0x69,0xe7,0x96,0xd3,0xa6,0x97,0xd2,0xa5,0x95,0xdc,
0xd5,0x8a,0x6a,0xbb,0xcd,0xa7,0x63,0xe3,0x23,0x4a,0x67,0xd3,0xdb,0xd9,0x00
}; // 31b vs 32b uncompressed
const uint8_t PROGMEM minifu1_comp_a[] = {
0x0f,0x0f,0x56,0xd2,0x95,0x92,0x69,0xe7,0x96,0xd3,0xa6,0x97,0xd2,0xa5,0x95,0xdc,
0xd5,0x8a,0x6a,0xbb,0xcd,0xa7,0x63,0xe3,0x23,0x4a,0x67,0xd3,0xdb,0xd9,0x00
}; // 31b vs 32b uncompressed