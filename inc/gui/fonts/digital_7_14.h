/* test comment */
const size_t digital_7_14_imageWidth = 98;
const size_t digital_7_14_imageHeight = 64;
const u8_t digital_7_14_x[] = { 
90,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
16,
96,
85,
49,
0,
6,
13,
89,
5,
9,
64,
68,
3,
11,
6,
12,
18,
17,
30,
36,
42,
48,
34,
60,
66,
72,
47,
45,
56,
80,
60,
12,
18,
24,
30,
36,
42,
48,
54,
60,
66,
96,
72,
78,
84,
90,
21,
82,
6,
27,
12,
18,
24,
30,
33,
36,
42,
48,
54,
13,
60,
94,
74,
5,
0,
66,
72,
78,
84,
40,
46,
52,
58,
95,
64,
70,
76,
88,
39,
0,
6,
20,
24,
0,
54,
78,
27,
84,
90,
0,
6,
90,
19,
0,
91,
}; 
const u8_t digital_7_14_y[] = { 
55,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
50,
10,
40,
40,
0,
0,
0,
40,
42,
40,
40,
40,
52,
50,
40,
10,
10,
40,
10,
10,
10,
10,
0,
10,
10,
10,
40,
40,
40,
40,
40,
20,
20,
20,
20,
20,
20,
20,
20,
20,
20,
20,
20,
20,
20,
20,
40,
0,
30,
0,
30,
30,
30,
30,
40,
30,
30,
30,
30,
40,
30,
0,
40,
52,
52,
30,
30,
30,
30,
0,
0,
0,
0,
30,
0,
0,
0,
0,
40,
12,
10,
0,
10,
32,
10,
10,
40,
10,
10,
22,
20,
30,
40,
42,
40,
}; 
const u8_t digital_7_14_yPadding[] = { 
2,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
11,
2,
2,
4,
1,
2,
3,
2,
2,
2,
4,
5,
10,
6,
10,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
4,
4,
4,
5,
4,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
3,
2,
2,
2,
2,
2,
2,
2,
3,
2,
2,
2,
2,
2,
2,
2,
2,
10,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
3,
2,
2,
2,
2,
2,
2,
2,
3,
2,
2,
2,
2,
2,
2,
2,
5,
}; 
const u8_t digital_7_14_width[] = { 
5,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
1,
1,
3,
6,
5,
6,
6,
1,
3,
3,
3,
5,
1,
4,
1,
5,
5,
5,
5,
5,
5,
5,
5,
5,
5,
5,
1,
1,
3,
4,
3,
5,
5,
5,
5,
5,
5,
5,
5,
5,
5,
1,
5,
5,
5,
5,
5,
5,
5,
6,
5,
5,
5,
5,
5,
5,
5,
5,
5,
3,
5,
3,
5,
5,
2,
5,
5,
5,
5,
5,
5,
5,
5,
1,
5,
5,
5,
5,
5,
5,
5,
6,
5,
5,
5,
5,
5,
5,
5,
5,
5,
4,
1,
4,
6,
}; 
const u8_t digital_7_14_height[] = { 
9,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
1,
9,
3,
6,
11,
9,
9,
3,
9,
9,
5,
4,
2,
1,
1,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
7,
8,
5,
3,
5,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
8,
9,
9,
9,
9,
9,
9,
9,
8,
9,
9,
9,
9,
9,
9,
9,
4,
1,
2,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
8,
9,
9,
9,
9,
9,
9,
9,
8,
9,
9,
9,
9,
9,
9,
9,
2,
}; 
const u8_t digital_7_14_data[] = { 
0x38,
0x22,
0x22,
0xB9,
0x01,
0x00,
0xE0,
0xA1,
0xE6,
0x33,
0xC2,
0x03,
0x00,
0x0F,
0xF1,
0x91,
0x91,
0xF1,
0x0E,
0x00,
0xF7,
0x80,
0x80,
0x81,
0xF7,
0x00,
0x00,
0xF7,
0x80,
0x80,
0x81,
0xF7,
0x00,
0x00,
0xF7,
0x88,
0x88,
0x88,
0x07,
0x00,
0x77,
0x88,
0x88,
0x88,
0x88,
0x00,
0x77,
0x88,
0x88,
0x88,
0x88,
0x00,
0xF7,
0x80,
0x88,
0x88,
0x07,
0x00,
0x7F,
0x08,
0x08,
0x08,
0xF7,
0x00,
0x07,
0x00,
0x00,
0x00,
0xF7,
0x00,
0xF7,
0x18,
0x28,
0x48,
0x87,
0x00,
0xF7,
0x00,
0x00,
0x00,
0x00,
0x00,
0x7F,
0x80,
0x80,
0x80,
0xFF,
0x00,
0xF7,
0x80,
0xB8,
0x80,
0xF7,
0x00,
0x00,
0x80,
0xF7,
0x00,
0x47,
0x48,
0x48,
0x48,
0xCF,
0x00,
0x3D,
0xA2,
0x22,
0xA2,
0x9C,
0x80,
0x00,
0x00,
0x01,
0x0C,
0x30,
0x00,
0xBD,
0x20,
0xA0,
0xA0,
0xBD,
0x80,
0xBD,
0xA3,
0x22,
0xA2,
0xBC,
0x80,
0xA1,
0xA2,
0xA2,
0x22,
0xBC,
0x80,
0xA2,
0xA2,
0xA2,
0x22,
0xBD,
0x80,
0x9C,
0x82,
0x02,
0x02,
0xBD,
0x00,
0x3C,
0x22,
0x22,
0x22,
0x81,
0x80,
0x80,
0xA0,
0xAF,
0x20,
0xA0,
0x00,
0x3C,
0x20,
0xA0,
0x20,
0xBD,
0x80,
0xBD,
0xA2,
0xA2,
0x22,
0xBD,
0x00,
0x3C,
0x22,
0xA2,
0x22,
0xBD,
0x80,
0x9F,
0x80,
0x80,
0x00,
0x3D,
0x80,
0xBD,
0x80,
0x81,
0x00,
0xBD,
0x00,
0x30,
0x0D,
0x80,
0x0D,
0x30,
0x80,
0xBD,
0x00,
0xF1,
0x08,
0x08,
0x08,
0xFB,
0x00,
0xE0,
0x08,
0x08,
0x0B,
0x0C,
0x00,
0x28,
0xE8,
0x88,
0x08,
0x0F,
0x00,
0xEF,
0x28,
0x2B,
0x2A,
0xEF,
0x00,
0xEF,
0x08,
0x88,
0x48,
0x2F,
0x00,
0xEF,
0x28,
0x28,
0x28,
0x07,
0x00,
0x27,
0x28,
0x28,
0x28,
0xE8,
0x00,
0x0F,
0x08,
0x08,
0x08,
0xE7,
0x00,
0x27,
0x28,
0x28,
0x28,
0xE8,
0x00,
0x07,
0x08,
0xE8,
0x08,
0x08,
0x00,
0x0F,
0x08,
0x08,
0x08,
0xE0,
0x00,
0xE7,
0x20,
0x20,
0x20,
0xEF,
0x00,
0x20,
0x20,
0x20,
0x20,
0xEF,
0x00,
0xEF,
0x21,
0x22,
0x24,
0xE8,
0x00,
0xEF,
0x20,
0xE0,
0x20,
0xE0,
0x00,
0x6F,
0x88,
0x0B,
0x88,
0x6F,
0x00,
0xAF,
0x00,
0xC2,
0x22,
0x22,
0x22,
0xDE,
0x00,
0x0B,
0x1A,
0x6A,
0x0A,
0x09,
0x00,
0x6B,
0x82,
0x82,
0x82,
0x03,
0x00,
0x7B,
0x0A,
0x6A,
0x2A,
0x62,
0x00,
0x78,
0x82,
0x82,
0x82,
0x7A,
0x00,
0x79,
0x88,
0x88,
0x88,
0xF3,
0x00,
0x7B,
0x08,
0x08,
0x08,
0x03,
0x00,
0x7B,
0x08,
0x08,
0x08,
0xF3,
0x00,
0x79,
0x88,
0x88,
0x88,
0x83,
0x00,
0x78,
0x82,
0x82,
0x82,
0x83,
0x00,
0x7A,
0x0B,
0x88,
0x88,
0x78,
0x00,
0xFB,
0x82,
0x82,
0x82,
0x7B,
0x00,
0x7B,
0x0A,
0x0A,
0x0A,
0x79,
0x00,
0x79,
0x82,
0x82,
0x82,
0x7A,
0x00,
0x7B,
0x0A,
0x0A,
0x0A,
0x09,
0x00,
0x78,
0x00,
0x83,
0x02,
0x78,
0x03,
0x78,
0x00,
0xF0,
0x88,
0x88,
0x88,
0x87,
0x00,
0xDE,
0x20,
0x20,
0x20,
0xC0,
0x00,
0xDE,
0x30,
0x28,
0x24,
0xC2,
0x00,
0xC2,
0x22,
0x22,
0x22,
0x1E,
0x00,
0x00,
0x00,
0xFE,
0x00,
0x00,
0x00,
0xFE,
0x02,
0x02,
0x02,
0xDE,
0x00,
0xDE,
0x02,
0x1E,
0x02,
0xDE,
0x00,
0x06,
0xD8,
0x00,
0xD8,
0x06,
0x00,
0xC2,
0x22,
0x22,
0x22,
0xDE,
0x00,
0x02,
0x06,
0x1A,
0xC2,
0x02,
0x00,
0x00,
0x80,
0xC0,
0x18,
0x06,
0x00,
0xDE,
0x20,
0x20,
0x20,
0xDE,
0x00,
0xDE,
0x22,
0x22,
0x22,
0xFC,
0x00,
0xDE,
0x02,
0x02,
0x02,
0x00,
0x00,
0xDE,
0x02,
0x02,
0x02,
0xFC,
0x00,
0x20,
0x20,
0xDE,
0x02,
0x00,
0xDE,
0x00,
0x00,
0xA0,
0xBD,
0x82,
0x82,
0x80,
0x1F,
0xA0,
0x20,
0x00,
0x80,
0x80,
0x7F,
0x00,
0x77,
0x80,
0x80,
0x00,
0x00,
0x00,
0x00,
0x00,
0xF7,
0x00,
0x40,
0x20,
0xFF,
0x00,
0xFC,
0x06,
0x00,
0x06,
0xFC,
0x00,
0xFC,
0x06,
0x00,
0x06,
0xFC,
0x00,
0xFF,
0x00,
0x40,
0x20,
0xFF,
0x00,
0x83,
0x00,
0x82,
0x00,
0x50,
0x50,
0xFC,
0xFC,
0x50,
0x50,
0x00,
0x00,
0x50,
0x88,
0x00,
0x88,
0xD8,
0x50,
0x00,
0x50,
0xF8,
0x50,
0x00,
0x40,
0x40,
0xF0,
0x40,
0x40,
0x00,
0x10,
0x20,
0xC0,
0x40,
0x20,
0x00,
0xA0,
0xA0,
0xA0,
0xA0,
0x00,
0xE0,
0x00,
0xE0,
0x00,
0xE0,
0x00,
0x80,
0x80,
0x80,
0xC0,
0xC0,
0x80,
0x00,
0x28,
0xE4,
0x00,
0x0C,
0x00,
0xC0,
0x28,
0x28,
0x08,
0x88,
0x80,
0x20,
0x20,
0x20,
0xA0,
0x80,
0x00,
0x00,
0x00,
0x00,
0x00,
0x80,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
}; 
