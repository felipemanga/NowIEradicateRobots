/*
-------  -------
--- --    -- ---
  - -      - -  
    -      -    
                
-              -
--            --
-    -    -    -
-   - -  - -   -
-  ----  ----  -
---- --  -- ----
-------  -------
-------  -------
-------  -------
-------  -------
-------  -------
*/



const unsigned char PROGMEM minifu2[] = {
// width, height,
16, 16,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


const unsigned char PROGMEM minifu2_mask[] = {
0x1c,0xbc,0xf8,0xfe,0xf0,0x7c,0xfe,0xff,0xff,0xfe,0x7c,0xf0,0xfe,0xf8,0xbc,0x1c,
0x00,0x03,0x03,0x01,0x04,0x01,0x00,0xff,0xff,0x00,0x01,0x04,0x01,0x03,0x03,0x00
};



const unsigned char PROGMEM minifu2_plus_mask[] = {
// width, height,
16, 16,
0x00, 0x1c,0x00, 0xbc,0x00, 0xf8,0x00, 0xfe,0x00, 0xf0,0x00, 0x7c,0x00, 0xfe,0x00, 0xff,0x00, 0xff,0x00, 0xfe,0x00, 0x7c,0x00, 0xf0,0x00, 0xfe,0x00, 0xf8,0x00, 0xbc,0x00, 0x1c,
0x00, 0x00,0x00, 0x03,0x00, 0x03,0x00, 0x01,0x00, 0x04,0x00, 0x01,0x00, 0x00,0x00, 0xff,0x00, 0xff,0x00, 0x00,0x00, 0x01,0x00, 0x04,0x00, 0x01,0x00, 0x03,0x00, 0x03,0x00, 0x00
};


const uint8_t PROGMEM minifu2_comp_w[] = {
0x0f,0x0f,0xe0,0x3f
}; // 4b vs 32b uncompressed
const uint8_t PROGMEM minifu2_comp_b[] = {
0x0f,0x0f,0x56,0xd2,0x95,0x92,0x69,0xe7,0x96,0xd3,0xa6,0x97,0xd2,0xa5,0x95,0xdc,
0xd5,0x8a,0x6a,0xbb,0x8d,0x28,0x19,0x1d,0x9f,0x8f,0x28,0x99,0xde,0xce,0x06
}; // 31b vs 32b uncompressed
const uint8_t PROGMEM minifu2_comp_a[] = {
0x0f,0x0f,0x56,0xd2,0x95,0x92,0x69,0xe7,0x96,0xd3,0xa6,0x97,0xd2,0xa5,0x95,0xdc,
0xd5,0x8a,0x6a,0xbb,0x8d,0x28,0x19,0x1d,0x9f,0x8f,0x28,0x99,0xde,0xce,0x06
}; // 31b vs 32b uncompressed
