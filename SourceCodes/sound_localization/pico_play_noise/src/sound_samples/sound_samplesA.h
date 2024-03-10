#include <stddef.h> // for size_t
#include <stdint.h> // for uint16_t

#define SOUND_SAMPLES_LEN 4096

//These are actually signed ints 
const uint16_t sound_samples[SOUND_SAMPLES_LEN] = {
    0x0000, 0x1014, 0x1FF9, 0x2F6E, 0x3E2F, 0x4BFC, 0x5897, 0x63C7, 0x6D54, 0x7511,
    0x7AD5, 0x7E7F, 0x7FF7, 0x7F31, 0x7C27, 0x76E0, 0x6F6D, 0x65EA, 0x5A7D, 0x4D55,
    0x3EAD, 0x2EC6, 0x1DEB, 0x0C6A, 0xFA9A, 0xE8D1, 0xD76A, 0xC6BE, 0xB727, 0xA8F7,
    0x9C7D, 0x9201, 0x89C0, 0x83ED, 0x80AF, 0x8020, 0x824A, 0x872C, 0x8EB0, 0x98B7,
    0xA50D, 0xB375, 0xC3A1, 0xD53A, 0xE7DD, 0xFB20, 0x0E91, 0x21C0, 0x3436, 0x4583,
    0x553A, 0x62F4, 0x6E58, 0x7718, 0x7CF5, 0x7FC2, 0x7F64, 0x7BD4, 0x7521, 0x6B6E,
    0x5EF1, 0x4FF6, 0x3ED9, 0x2C07, 0x17FB, 0x033A, 0xEE51, 0xD9CE, 0xC642, 0xB438,
    0xA433, 0x96AB, 0x8C07, 0x849B, 0x80A7, 0x804F, 0x83A0, 0x8A8B, 0x94E6, 0xA26C,
    0xB2C0, 0xC56C, 0xD9E9, 0xEF9B, 0x05DF, 0x1C08, 0x3168, 0x4554, 0x5729, 0x6652,
    0x724F, 0x7AB7, 0x7F3B, 0x7FAD, 0x7C00, 0x7446, 0x68B8, 0x59AD, 0x479C, 0x331A,
    0x1CCF, 0x0579, 0xEDE2, 0xD6D5, 0xC122, 0xAD8B, 0x9CC4, 0x8F6C, 0x8603, 0x80E8,
    0x8054, 0x8457, 0x8CD6, 0x998E, 0xAA10, 0xBDC9, 0xD406, 0xEBF8, 0x04BC, 0x1D65,
    0x3503, 0x4AAD, 0x5D89, 0x6CD5, 0x77F1, 0x7E64, 0x7FE4, 0x7C55, 0x73D0, 0x66A2,
    0x5549, 0x406E, 0x28E5, 0x0F9D, 0xF59F, 0xDBFC, 0xC3C7, 0xAE06, 0x9BAA, 0x8D82,
    0x8431, 0x8029, 0x81A0, 0x8893, 0x94BF, 0xA5A8, 0xBA97, 0xD2A9, 0xECD1, 0x07E6,
    0x22B4, 0x3C02, 0x52A5, 0x658F, 0x73D9, 0x7CD0, 0x7FFE, 0x7D30, 0x747D, 0x6642,
    0x5320, 0x3BF8, 0x21DF, 0x0612, 0xE9E7, 0xCEBD, 0xB5EC, 0xA0B2, 0x9024, 0x851F,
    0x803B, 0x81C3, 0x89B0, 0x97A8, 0xAAFF, 0xC2C2, 0xDDBE, 0xFA93, 0x17C2, 0x33C6,
    0x4D20, 0x6274, 0x7297, 0x7CA2, 0x7FFE, 0x7C71, 0x721E, 0x618A, 0x4B90, 0x315E,
    0x145F, 0xF62C, 0xD873, 0xBCE1, 0xA509, 0x924D, 0x85C9, 0x803F, 0x820F, 0x8B2B,
    0x9B19, 0xB0F6, 0xCB86, 0xE93E, 0x0861, 0x2718, 0x438A, 0x5BFC, 0x6EEE, 0x7B2E,
    0x7FF2, 0x7CE1, 0x721D, 0x6044, 0x4864, 0x2BF1, 0x0CAB, 0xEC88, 0xCD8D, 0xB1B6,
    0x9ACF, 0x8A5A, 0x8172, 0x80B7, 0x8845, 0x97AB, 0xADF3, 0xC9B2, 0xE919, 0x0A18,
    0x2A7D, 0x481A, 0x60EB, 0x7338, 0x7DB8, 0x7FA6, 0x78D1, 0x69A3, 0x531B, 0x36BF,
    0x1680, 0xF49C, 0xD371, 0xB55D, 0x9C86, 0x8ABD, 0x8153, 0x8104, 0x89E5, 0x9B5F,
    0xB43B, 0xD2B1, 0xF48D, 0x1753, 0x3871, 0x556C, 0x6C12, 0x7AA3, 0x7FFB, 0x7BA2,
    0x6DDD, 0x57AC, 0x3AB3, 0x1926, 0xF595, 0xD2C1, 0xB362, 0x99F4, 0x8881, 0x8076,
    0x8285, 0x8E94, 0xA3BC, 0xC058, 0xE225, 0x066D, 0x2A43, 0x4AB7, 0x651C, 0x773D,
    0x7F8C, 0x7D4C, 0x709A, 0x5A78, 0x3CB2, 0x19C0, 0xF48F, 0xD044, 0xAFF9, 0x9679,
    0x85FF, 0x8004, 0x851D, 0x94EA, 0xAE18, 0xCE81, 0xF355, 0x1958, 0x3D2F, 0x5BA5,
    0x71F9, 0x7E1D, 0x7EEB, 0x743F, 0x5F01, 0x4111, 0x1D1F, 0xF670, 0xD090, 0xAF01,
    0x94E8, 0x84BE, 0x8015, 0x876D, 0x9A27, 0xB68D, 0xD9FA, 0x0116, 0x282C, 0x4B77,
    0x678D, 0x79AA, 0x7FFE, 0x79DC, 0x67CA, 0x4B7E, 0x27B5, 0xFFEF, 0xD817, 0xB428,
    0x97BD, 0x85BE, 0x8007, 0x873E, 0x9ABA, 0xB88F, 0xDDBE, 0x0681, 0x2EAC, 0x5216,
    0x6D0D, 0x7CB7, 0x7F62, 0x74B4, 0x5DBB, 0x3CD4, 0x156C, 0xEBAE, 0xC407, 0xA2BA,
    0x8B63, 0x8095, 0x838B, 0x9405, 0xB049, 0xD551, 0xFF17, 0x2908, 0x4E84, 0x6B5C,
    0x7C4F, 0x7F6A, 0x7441, 0x5C02, 0x395A, 0x1025, 0xE50A, 0xBCEF, 0x9C6D, 0x8749,
    0x8002, 0x877F, 0x9CF6, 0xBDFA, 0xE6BF, 0x1289, 0x3C39, 0x5EE2, 0x7661, 0x7FDF,
    0x7A29, 0x65D9, 0x454E, 0x1C60, 0xEFF6, 0xC56A, 0xA1E9, 0x89D0, 0x801F, 0x8618,
    0x9B13, 0xBC8A, 0xE66A, 0x1388, 0x3E49, 0x6152, 0x7834, 0x7FFE, 0x77A2, 0x601C,
    0x3C56, 0x10D0, 0xE314, 0xB8FA, 0x97F4, 0x8451, 0x80AB, 0x8D90, 0xA965, 0xD099,
    0xFE14, 0x2BE1, 0x53F5, 0x70FB, 0x7F09, 0x7C2E, 0x68B8, 0x472F, 0x1C05, 0xED03,
    0xC081, 0x9C8D, 0x8617, 0x8041, 0x8BEC, 0xA791, 0xCF73, 0xFE1B, 0x2D18, 0x55E1,
    0x72BB, 0x7F8F, 0x7A7C, 0x6424, 0x3F9D, 0x1203, 0xE1C9, 0xB5CC, 0x945C, 0x8252,
    0x8258, 0x9483, 0xB645, 0xE2C9, 0x139E, 0x41A8, 0x6624, 0x7BAA, 0x7EFC, 0x6F88,
    0x4F84, 0x23A0, 0xF25D, 0xC311, 0x9CD9, 0x857F, 0x809C, 0x8F01, 0xAE94, 0xDA99,
    0x0C63, 0x3C5B, 0x631D, 0x7AA8, 0x7F46, 0x702D, 0x4F9E, 0x229A, 0xF01E, 0xC00C,
    0x99F9, 0x83EF, 0x817C, 0x931A, 0xB610, 0xE4DE, 0x1813, 0x477E, 0x6B79, 0x7E29,
    0x7C75, 0x668F, 0x3FF0, 0x0ED5, 0xDB3D, 0xAD9A, 0x8D77, 0x8030, 0x880C, 0xA3D4,
    0xCEFC, 0x0260, 0x3571, 0x5F9B, 0x79BD, 0x7F5B, 0x6F6D, 0x4C91, 0x1CA2, 0xE7C0,
    0xB6F2, 0x929C, 0x810D, 0x8560, 0x9EEB, 0xC957, 0xFD53, 0x31D7, 0x5DB6, 0x7934,
    0x7F69, 0x6F29, 0x4B3B, 0x19EB, 0xE3EF, 0xB2E2, 0x8F8D, 0x8055, 0x8809, 0xA55E,
    0xD31D, 0x090B, 0x3D68, 0x66A6, 0x7D33, 0x7CDA, 0x6595, 0x3B95, 0x0688, 0xD035,
    0xA2AE, 0x8676, 0x80E0, 0x930F, 0xB9B2, 0xED9A, 0x2508, 0x558A, 0x75E5, 0x7FE5,
    0x718A, 0x4D7C, 0x1A8C, 0xE274, 0xAFF9, 0x8CE0, 0x8003, 0x8BF5, 0xAE7D, 0xE0F4,
    0x198C, 0x4D35, 0x71C2, 0x7FF1, 0x74E0, 0x52A7, 0x1FFB, 0xE6E3, 0xB2BB, 0x8DF8,
    0x8008, 0x8BCE, 0xAF04, 0xE2A2, 0x1C42, 0x5037, 0x73E7, 0x7FF9, 0x71DF, 0x4C64,
    0x1728, 0xDD16, 0xAA29, 0x88F7, 0x8074, 0x927F, 0xBB6B, 0xF2BE, 0x2CE9, 0x5DB4,
    0x7ACC, 0x7DF8, 0x6674, 0x3926, 0xFFA0, 0xC61D, 0x98EB, 0x81C9, 0x85C4, 0xA41A,
    0xD654, 0x11A2, 0x492F, 0x70DE, 0x7FF8, 0x7319, 0x4CFA, 0x15E4, 0xD9EC, 0xA64B,
    0x8677, 0x8193, 0x98CC, 0xC710, 0x021A, 0x3CBE, 0x69CE, 0x7F19, 0x77BB, 0x5546,
    0x1F71, 0xE268, 0xAC0B, 0x88CA, 0x80CA, 0x95F7, 0xC38E, 0xFF21, 0x3AF7, 0x6937,
    0x7F17, 0x7769, 0x53DE, 0x1CAE, 0xDEB6, 0xA87E, 0x86D1, 0x81B5, 0x9A76, 0xCB52,
    0x08C0, 0x4429, 0x6F5E, 0x7FF7, 0x71E4, 0x486B, 0x0D73, 0xCF2D, 0x9CA6, 0x822C,
    0x8645, 0xA80B, 0xDF58, 0x1EB1, 0x5695, 0x793B, 0x7E08, 0x63B1, 0x30A2, 0xF173,
    0xB5D2, 0x8CA0, 0x8038, 0x93CF, 0xC295, 0x00DA, 0x3EFA, 0x6D40, 0x7FE5, 0x7217,
    0x473D, 0x0A2D, 0xCA73, 0x9860, 0x80D9, 0x8A04, 0xB19F, 0xED86, 0x2E45, 0x6313,
    0x7E28, 0x785F, 0x5320, 0x1812, 0xD6A3, 0xA005, 0x82A5, 0x865D, 0xAA4C, 0xE502,
    0x26F4, 0x5E96, 0x7D03, 0x7A00, 0x5642, 0x1B49, 0xD8E8, 0xA103, 0x82C5, 0x8675,
    0xAB30, 0xE70D, 0x29C9, 0x6128, 0x7DF3, 0x782B, 0x514C, 0x13F4, 0xD109, 0x9B10,
    0x8111, 0x8A5E, 0xB47B, 0xF3BE, 0x367F, 0x6A06, 0x7FC8, 0x718B, 0x4339, 0x01D4,
    0xBFDB, 0x900C, 0x8015, 0x949D, 0xC7E2, 0x0B48, 0x4B83, 0x7611, 0x7E9B, 0x628F,
    0x29EF, 0xE516, 0xA800, 0x8481, 0x850B, 0xA993, 0xE77C, 0x2CA9, 0x64C0, 0x7F29,
    0x73FD, 0x4670, 0x03ED, 0xC02F, 0x8F68, 0x8039, 0x9748, 0xCDC8, 0x136C, 0x5349,
    0x7A11, 0x7BF6, 0x5849, 0x19C3, 0xD359, 0x9A7A, 0x8094, 0x8DAB, 0xBDD9, 0x0268,
    0x464A, 0x748A, 0x7EC9, 0x61C0, 0x2655, 0xDEEF, 0xA1C7, 0x8200, 0x89A3, 0xB669,
    0xFA59, 0x4021, 0x71BD, 0x7F6F, 0x64C5, 0x2A17, 0xE1FA, 0xA35D, 0x8246, 0x8962,
    0xB687, 0xFB50, 0x41AB, 0x72E9, 0x7F11, 0x6218, 0x2546, 0xDC49, 0x9EDD, 0x8115,
    0x8CC5, 0xBE38, 0x054C, 0x4AB4, 0x778D, 0x7CF9, 0x590E, 0x1797, 0xCE3D, 0x9560,
    0x8002, 0x955F, 0xCE71, 0x182C, 0x59DA, 0x7D58, 0x7699, 0x47C5, 0x009A, 0xB92C,
    0x89C0, 0x828C, 0xA623, 0xE879, 0x32EB, 0x6BF6, 0x7FF2, 0x67E1, 0x2BF2, 0xE0C6,
    0xA05A, 0x8110, 0x8DE3, 0xC278, 0x0C91, 0x5257, 0x7B53, 0x7910, 0x4C3A, 0x0480,
    0xBB20, 0x8A0B, 0x82B5, 0xA7D7, 0xEC5A, 0x37EB, 0x6F98, 0x7F69, 0x6197, 0x20B8,
    0xD408, 0x971E, 0x8001, 0x9729, 0xD450, 0x215F, 0x625C, 0x7F93, 0x6E41, 0x349C,
    0xE7A6, 0xA38F, 0x8166, 0x8DD7, 0xC46A, 0x110F, 0x5774, 0x7D75, 0x74DC, 0x40BE,
    0xF46F, 0xAC62, 0x8394, 0x8969, 0xBBCF, 0x07EA, 0x511A, 0x7BB4, 0x7786, 0x4604,
    0xF9E1, 0xB001, 0x8492, 0x883D, 0xB9BB, 0x0631, 0x5057, 0x7BA5, 0x7757, 0x44F6,
    0xF7E1, 0xADE1, 0x83B1, 0x89CD, 0xBDF3, 0x0BE9, 0x5547, 0x7D50, 0x743A, 0x3D76,
    0xEE77, 0xA651, 0x818A, 0x8EC7, 0xC8E8, 0x18F6, 0x5F26, 0x7F79, 0x6CEF, 0x2ED2,
    0xDDE7, 0x9A9A, 0x8003, 0x98F2, 0xDB79, 0x2CCE, 0x6C12, 0x7F8E, 0x5F3E, 0x1825,
    0xC728, 0x8D50, 0x8256, 0xAAD8, 0xF656, 0x45DB, 0x78AB, 0x79BC, 0x487D, 0xF933,
    0xACAB, 0x82B2, 0x8CD6, 0xC6FE, 0x18FE, 0x609A, 0x7FCB, 0x695F, 0x26A2, 0xD394,
    0x9332, 0x80BF, 0xA425, 0xEE84, 0x405E, 0x76E6, 0x7ACD, 0x4A49, 0xF9F9, 0xAC2E,
    0x824B, 0x8E66, 0xCB6A, 0x1F26, 0x657F, 0x7FFB, 0x6305, 0x1B0E, 0xC747, 0x8C23,
    0x8381, 0xB146, 0x0188, 0x512E, 0x7D3B, 0x723A, 0x34E1, 0xE026, 0x9970, 0x8018,
    0x9F78, 0xE9C1, 0x3DFE, 0x76A8, 0x7A62, 0x4761, 0xF45D, 0xA682, 0x80D1, 0x945B,
    0xD873, 0x2E73, 0x6F80, 0x7E13, 0x536F, 0x02D6, 0xB0E4, 0x82F7, 0x8E21, 0xCD68,
    0x23E9, 0x69FF, 0x7F65, 0x5A22, 0x0B45, 0xB725, 0x84AD, 0x8B56, 0xC82A, 0x1EFF,
    0x6775, 0x7FB4, 0x5C4B, 0x0DAA, 0xB894, 0x84F7, 0x8B2D, 0xC86B, 0x1FEC, 0x6868,
    0x7F87, 0x5A36, 0x0A0A, 0xB50B, 0x83AF, 0x8D99, 0xCE2E, 0x26A5, 0x6CA6, 0x7E8B,
    0x539A, 0x005E, 0xACE8, 0x8186, 0x9350, 0xD9C9, 0x32DA, 0x7343, 0x7B97, 0x47A7,
    0xF0AF, 0xA126, 0x8009, 0x9DB2, 0xEBB1, 0x43BC, 0x7A72, 0x74BB, 0x3547, 0xDB66,
    0x939D, 0x81A2, 0xAE87, 0x040E, 0x579E, 0x7F6E, 0x6776, 0x1B97, 0xC1D1, 0x8743,
    0x897F, 0xC787, 0x2223, 0x6B88, 0x7E77, 0x5135, 0xFAA2, 0xA6BB, 0x804E, 0x9B15,
    0xE980, 0x437F, 0x7AEB, 0x7335, 0x3032, 0xD44D, 0x8EE7, 0x83EF, 0xB934, 0x1338,
    0x6350, 0x7FCC, 0x59B9, 0x04D0, 0xAD56, 0x810F, 0x9748, 0xE47C, 0x4033, 0x7A2D,
    0x73C6, 0x303C, 0xD326, 0x8DC1, 0x84EA, 0xBD73, 0x196C, 0x67E9, 0x7F01, 0x523F,
    0xF972, 0xA41A, 0x8008, 0xA0BA, 0xF4BB, 0x4EDC, 0x7E79, 0x69BA, 0x1BB6, 0xBEA0,
    0x84FC, 0x8E38, 0xD570, 0x33EA, 0x7618, 0x77B4, 0x37B9, 0xD922, 0x8FD7, 0x843A,
    0xBCD3, 0x1A87, 0x69A2, 0x7E4F, 0x4CFB, 0xF0E4, 0x9D24, 0x8062, 0xAAC3, 0x04C3,
    0x5C28, 0x7FFE, 0x5C13, 0x046C, 0xAA3B, 0x804B, 0x9E5D, 0xF39A, 0x4FE7, 0x7F00,
    0x6613, 0x1325, 0xB547, 0x81EC, 0x9679, 0xE754, 0x4659, 0x7D1E, 0x6C20, 0x1CFC,
    0xBD20, 0x83BE, 0x9209, 0xDFE3, 0x405E, 0x7B9A, 0x6F23, 0x2212, 0xC122, 0x84C7,
    0x904F, 0xDD21, 0x3E67, 0x7B29, 0x6FAA, 0x2286, 0xC106, 0x8495, 0x90F5, 0xDEFA,
    0x4096, 0x7BF8, 0x6DCE, 0x1E5C, 0xBCCE, 0x833D, 0x941D, 0xE57C, 0x46C5, 0x7DB2,
    0x6935, 0x1579, 0xB4C5, 0x8159, 0x9A58, 0xF0CB, 0x507E, 0x7F77, 0x611B, 0x07B7,
    0xA995, 0x800E, 0xA495, 0x00FE, 0x5CDA, 0x7FDD, 0x5470, 0xF51C, 0x9C6D, 0x810B,
    0xB3FA, 0x15E7, 0x6A56, 0x7CF1, 0x420D, 0xDE1A, 0x8F2E, 0x867D, 0xC995, 0x2EB3,
    0x76AB, 0x745C, 0x2914, 0xC3F7, 0x848B, 0x92D2, 0xE5F2, 0x4990, 0x7EBB, 0x63B3,
    0x0974, 0xA929, 0x8002, 0xA84C, 0x087F, 0x6355, 0x7EBD, 0x4910, 0xE48C, 0x9197,
    0x8584, 0xC83C, 0x2EE8, 0x7761, 0x72CA, 0x23F5, 0xBDCD, 0x8283, 0x98AC, 0xF206,
    0x5485, 0x7FF9, 0x57EA, 0xF660, 0x9B15, 0x81E0, 0xBB6B, 0x220D, 0x7256, 0x7757,
    0x2DA0, 0xC5BC, 0x8453, 0x94C9, 0xEC5A, 0x5102, 0x7FDD, 0x599E, 0xF79F, 0x9B29,
    0x820C, 0xBD36, 0x2527, 0x743A, 0x7542, 0x2769, 0xBEFB, 0x8259, 0x9A89, 0xF758,
    0x5A0F, 0x7FC7, 0x4EC7, 0xE836, 0x91C8, 0x866A, 0xCE00, 0x37C7, 0x7B75, 0x6A9C,
    0x10A4, 0xAB33, 0x8003, 0xACEA, 0x131D, 0x6C2C, 0x7A85, 0x3417, 0xC98A, 0x84B6,
    0x957D, 0xF05B, 0x5629, 0x7FF0, 0x506B, 0xE8A9, 0x912F, 0x8754, 0xD224, 0x3D36,
    0x7D47, 0x6522, 0x05A7, 0xA223, 0x80EF, 0xB9AB, 0x2448, 0x7533, 0x72E0, 0x1ED2,
    0xB4C5, 0x8053, 0xA709, 0x0D61, 0x6A32, 0x7AEF, 0x3372, 0xC6F4, 0x8374, 0x99A6,
    0xF9AF, 0x5E53, 0x7ECF, 0x4380, 0xD73C, 0x8880, 0x9093, 0xE9B9, 0x5325, 0x7FF9,
    0x4F5D, 0xE4B4, 0x8DF9, 0x8AC9, 0xDD9F, 0x49C1, 0x7FAE, 0x5794, 0xEEDF, 0x92C2,
    0x875F, 0xD546, 0x42E0, 0x7EE9, 0x5CAF, 0xF580, 0x9616, 0x859B, 0xD07F, 0x3EEE,
    0x7E52, 0x5F16, 0xF882, 0x9781, 0x850B, 0xCF28, 0x3E1F, 0x7E41, 0x5F01, 0xF7DD,
    0x96D6, 0x8586, 0xD134, 0x407F, 0x7EBF, 0x5C6F, 0xF395, 0x942A, 0x872E, 0xD6B6,
    0x45EE, 0x7F86, 0x5724, 0xEBB2, 0x8FD7, 0x8A73, 0xDFD4, 0x4E1E, 0x7FFE, 0x4EB4,
    0xE055, 0x8A81, 0x9005, 0xECBB, 0x5880, 0x7F40, 0x4295, 0xD1CD, 0x8527, 0x98CE,
    0xFD7D, 0x6430, 0x7C17, 0x323C, 0xC0B9, 0x8121, 0xA5D3, 0x11EA, 0x6FDC, 0x7516,
    0x1D4E, 0xAE2E, 0x8027, 0xB806, 0x295D, 0x79B4, 0x68B8, 0x03DB, 0x9BDC, 0x8435,
    0xD00A, 0x427E, 0x7F6F, 0x55A0, 0xE6A9, 0x8C22, 0x8F57, 0xEDD5, 0x5B1A, 0x7E6F,
    0x3AFB, 0xC77D, 0x8200, 0xA349, 0x1050, 0x700D, 0x7417, 0x18FA, 0xA955, 0x80D6,
    0xC0EA, 0x34F6, 0x7D67, 0x5E61, 0xF15D, 0x9068, 0x8BD3, 0xE790, 0x579E, 0x7EEB,
    0x3CA5, 0xC7D7, 0x81D0, 0xA517, 0x145B, 0x72A4, 0x70F1, 0x1088, 0xA236, 0x82AA,
    0xCC90, 0x41D2, 0x7F9F, 0x51B4, 0xDEB6, 0x87D7, 0x96B8, 0xFEE5, 0x680C, 0x78CF,
    0x22C7, 0xAF17, 0x805A, 0xBE95, 0x34C0, 0x7DD4, 0x5B26, 0xEA49, 0x8C05, 0x9167,
    0xF5F6, 0x6334, 0x7AF1, 0x288C, 0xB313, 0x801E, 0xBBEB, 0x32C7, 0x7D9C, 0x5B4C,
    0xE98A, 0x8B4C, 0x92C9, 0xF99E, 0x6611, 0x7943, 0x2242, 0xAD2E, 0x80C1, 0xC421,
    0x3C32, 0x7F4D, 0x5232, 0xDC87, 0x8628, 0x9B87, 0x09E0, 0x6F84, 0x723A, 0x0F75,
    0x9EE7, 0x84C1, 0xD873, 0x4F77, 0x7F8C, 0x3D96, 0xC478, 0x80A8, 0xAF10, 0x262E,
    0x7B04, 0x6129, 0xEFC0, 0x8CF4, 0x9202, 0xFA7F, 0x6801, 0x7756, 0x1A72, 0xA583,
    0x82C6, 0xD1F5, 0x4B1B, 0x7FD2, 0x3FE3, 0xC58D, 0x80A2, 0xB052, 0x2910, 0x7C2C,
    0x5D3D, 0xE88D, 0x8968, 0x9785, 0x0607, 0x6F03, 0x7166, 0x0AD5, 0x9A32, 0x87EF,
    0xE526, 0x5B59, 0x7C9A, 0x29CF, 0xB001, 0x80D2, 0xC874, 0x4412, 0x7FFE, 0x43F7,
    0xC825, 0x80BE, 0xB0FA, 0x2B9D, 0x7D33, 0x58B8, 0xE074, 0x85F6, 0x9EEB, 0x13D7,
    0x75FE, 0x682E, 0xF75F, 0x8EBA, 0x91E8, 0xFE07, 0x6C12, 0x72ED, 0x0BE5, 0x9972,
    0x8937, 0xEAEA, 0x60E4, 0x79C9, 0x1D83, 0xA4C8, 0x83F5, 0xDAD6, 0x55A7, 0x7DAD,
    0x2C0B, 0xAFB3, 0x8137, 0xCDD7, 0x4B40, 0x7F7B, 0x378C, 0xB96C, 0x8025, 0xC3C8,
    0x4257, 0x7FFD, 0x4036, 0xC16A, 0x800A, 0xBC73, 0x3B5B, 0x7FD6, 0x4645, 0xC752,
    0x8055, 0xB79C, 0x3695, 0x7F80, 0x49F0, 0xCAED, 0x80A2, 0xB514, 0x342D, 0x7F4A,
    0x4B5C, 0xCC1D, 0x80B9, 0xB4BF, 0x3436, 0x7F56, 0x4A9A, 0xCADA, 0x808B, 0xB69A,
    0x36B0, 0x7F9F, 0x47A1, 0xC72E, 0x8035, 0xBAB9, 0x3B88, 0x7FEF, 0x4252, 0xC135,
    0x8001, 0xC146, 0x4293, 0x7FE9, 0x3A78, 0xB929, 0x8063, 0xCA7A, 0x4B89, 0x7F04,
    0x2FDA, 0xAF65, 0x81F9, 0xD690, 0x55F9, 0x7C8D, 0x2242, 0xA474, 0x8586, 0xE5B3,
    0x613A, 0x77B1, 0x1193, 0x991E, 0x8BEC, 0xF7E8, 0x6C62, 0x6F86, 0xFDE6, 0x8E6F,
    0x9615, 0x0CF5, 0x7640, 0x6328, 0xE7A0, 0x85C0, 0xA4DA, 0x243E, 0x7D5A, 0x51D3,
    0xCF9A, 0x80A9, 0xB8DC, 0x3CA9, 0x7FFE, 0x3B18, 0xB735, 0x80EB, 0xD24A, 0x5488,
    0x7C65, 0x1F14, 0xA06E, 0x8844, 0xF0AB, 0x6995, 0x70F1, 0xFEAD, 0x8DCE, 0x981D,
    0x12A0, 0x790A, 0x5C82, 0xDBC6, 0x8246, 0xB12F, 0x35B8, 0x7FE4, 0x3EE5, 0xB95F,
    0x80D1, 0xD30F, 0x566B, 0x7B53, 0x1941, 0x9B7E, 0x8BE9, 0xFBC0, 0x704B, 0x6961,
    0xEE77, 0x86D5, 0xA4CE, 0x2774, 0x7E8C, 0x49B5, 0xC342, 0x8013, 0xCAC2, 0x5092,
    0x7CE5, 0x1E51, 0x9DF6, 0x8AD1, 0xFA5F, 0x703E, 0x68B8, 0xEC11, 0x85B2, 0xA85A,
    0x2D54, 0x7F74, 0x425F, 0xBA9F, 0x80F0, 0xD66E, 0x5AD5, 0x78BA, 0x0E33, 0x9396,
    0x93AD, 0x0E85, 0x78EE, 0x5A14, 0xD4DC, 0x80AC, 0xBD6B, 0x460D, 0x7ED4, 0x26D4,
    0xA270, 0x8905, 0xF7CD, 0x7001, 0x67CA, 0xE86E, 0x841E, 0xAE40, 0x367F, 0x7FFE,
    0x35E8, 0xAD94, 0x846F, 0xEA2C, 0x6933, 0x6E64, 0xF395, 0x8727, 0xA715, 0x2E68,
    0x7FC3, 0x3C51, 0xB288, 0x831C, 0xE58E, 0x66F1, 0x6FE8, 0xF5D0, 0x87A0, 0xA6A7,
    0x2E9D, 0x7FD2, 0x3AAB, 0xB069, 0x83ED, 0xE9CD, 0x69EA, 0x6CE4, 0xEF10, 0x8541,
    0xACE0, 0x3719, 0x7FF3, 0x30C9, 0xA796, 0x8797, 0xF70C, 0x7135, 0x6448, 0xDF8F,
    0x8196, 0xBAE1, 0x46FA, 0x7E05, 0x1DDB, 0x99D0, 0x9093, 0x0D65, 0x7A1E, 0x53AE,
    0xC849, 0x8020, 0xD27D, 0x5BEB, 0x761B, 0x0130, 0x8ACD, 0xA2A6, 0x2BEB, 0x7FD2,
    0x382D, 0xAC16, 0x8645, 0xF4FF, 0x7130, 0x630C, 0xDBB8, 0x80C9, 0xC1C1, 0x4F19,
    0x7B5C, 0x1009, 0x90F7, 0x9A8D, 0x2123, 0x7EE4, 0x400C, 0xB212, 0x8469, 0xEFAF,
    0x6F31, 0x64E4, 0xDD69, 0x80DA, 0xC24E, 0x5085, 0x7A85, 0x0BDA, 0x8E60, 0x9EB5,
    0x2898, 0x7FC1, 0x370B, 0xA95E, 0x8845, 0xFD67, 0x75D3, 0x5A2E, 0xCD15, 0x8010,
    0xD441, 0x5FA3, 0x7254, 0xF494, 0x853E, 0xB13F, 0x4105, 0x7E65, 0x1B68, 0x9597,
    0x96FE, 0x1DFA, 0x7ED3, 0x3E15, 0xAE26, 0x86A9, 0xFA2F, 0x752B, 0x5A3D, 0xCBBA,
    0x8031, 0xD89E, 0x63A2, 0x6EA3, 0xEB56, 0x829B, 0xBB6B, 0x4CAE, 0x7B03, 0x0A75,
    0x8C5D, 0xA3DC, 0x32AE, 0x7FD9, 0x2731, 0x9BA3, 0x9274, 0x17BA, 0x7E26, 0x4044,
    0xAE97, 0x871A, 0xFD7D, 0x772E, 0x5501, 0xC389, 0x8143, 0xE52D, 0x6C51, 0x6535,
    0xD90C, 0x801B, 0xCF91, 0x5EDF, 0x7113, 0xEE02, 0x82B0, 0xBD0D, 0x5007, 0x790A,
    0x019C, 0x8805, 0xADB7, 0x40C4, 0x7DB6, 0x1355, 0x8F2E, 0xA16C, 0x31DF, 0x7FC0,
    0x22E4, 0x9758, 0x97E0, 0x23ED, 0x7FD4, 0x3031, 0x9FCF, 0x90B5, 0x1755, 0x7E92,
    0x3B42, 0xA803, 0x8B80, 0x0C5D, 0x7C89, 0x4438, 0xAF82, 0x87DC, 0x032A, 0x7A33,
    0x4B3B, 0xB5F6, 0x856A, 0xFBD1, 0x77F1, 0x507A, 0xBB22, 0x83DC, 0xF656, 0x760F,
    0x541B, 0xBEDB, 0x82F2, 0xF2BA, 0x74C4, 0x5641, 0xC106, 0x8282, 0xF0FB, 0x7431,
    0x56FF, 0xC194, 0x8275, 0xF117, 0x7465, 0x565E, 0xC083, 0x82C7, 0xF30D, 0x755A,
    0x5458, 0xBDD8, 0x838B, 0xF6E0, 0x76F8, 0x50D7, 0xB9A7, 0x84E5, 0xFC92, 0x7913,
    0x4BBD, 0xB40E, 0x870F, 0x0422, 0x7B6B, 0x44E2, 0xAD3D, 0x8A53, 0x0D8B, 0x7DA7,
    0x3C18, 0xA57B, 0x8F0C, 0x18B6, 0x7F59, 0x3135, 0x9D24, 0x959E, 0x257A, 0x7FFE,
    0x241A, 0x94B3, 0x9E72, 0x338E, 0x7EFC, 0x14BB, 0x8CC6, 0xA9EC, 0x4287, 0x7BAC,
    0x032E, 0x8618, 0xB85F, 0x51C9, 0x7562, 0xEFB8, 0x8187, 0xC9FB, 0x6086, 0x6B79,
    0xDAD9, 0x8005, 0xDEBC, 0x6DBB, 0x5D69, 0xC558, 0x828E, 0xF657, 0x7836, 0x4ADF,
    0xB04C, 0x8A0F, 0x1022, 0x7EA4, 0x33D9, 0x9D1E, 0x9748, 0x2B09, 0x7FA5, 0x18C3,
    0x8D76, 0xAAA5, 0x4580, 0x79FA, 0xFA9A, 0x832B, 0xC413, 0x5D8E, 0x6CB0, 0xDAF2,
    0x8012, 0xE2D5, 0x70E1, 0x575C, 0xBC09, 0x85BF, 0x055E, 0x7D05, 0x3A5E, 0xA0A8,
    0x953B, 0x2949, 0x7FA6, 0x1711, 0x8BEF, 0xAEAC, 0x4B5A, 0x76FE, 0xEFF6, 0x8103,
    0xD106, 0x67BF, 0x623D, 0xC8A9, 0x8288, 0xF9CA, 0x7A72, 0x4203, 0xA5B3, 0x9215,
    0x2501, 0x7FD7, 0x18B3, 0x8C0A, 0xAF95, 0x4D6E, 0x7575, 0xEA98, 0x8056, 0xD8CC,
    0x6D1D, 0x5AC4, 0xBDA9, 0x8606, 0x0920, 0x7E44, 0x31D2, 0x98EC, 0x9E48, 0x39CE,
    0x7C75, 0xFF96, 0x8356, 0xC734, 0x62AE, 0x65DE, 0xCBB6, 0x825B, 0xFB5B, 0x7B8F,
    0x3C5F, 0x9F95, 0x985C, 0x320B, 0x7DFF, 0x060E, 0x84AD, 0xC34F, 0x6086, 0x673D,
    0xCCDA, 0x8252, 0xFC32, 0x7C09, 0x39C5, 0x9D04, 0x9B62, 0x3791, 0x7C8D, 0xFDE8,
    0x8289, 0xCC83, 0x678D, 0x5F7C, 0xC0E4, 0x85D7, 0x0BA3, 0x7F12, 0x299D, 0x924F,
    0xA8A8, 0x4965, 0x75C8, 0xE74A, 0x8004, 0xE41A, 0x748F, 0x4B8F, 0xAA3B, 0x9190,
    0x2901, 0x7F07, 0x0A32, 0x850E, 0xC485, 0x632F, 0x6305, 0xC429, 0x8541, 0x0B58,
    0x7F3B, 0x26A2, 0x8FE3, 0xAD93, 0x5007, 0x7182, 0xDBE8, 0x808C, 0xF30D, 0x7A80,
    0x3BD1, 0x9C4E, 0x9E44, 0x3EA8, 0x796D, 0xEF19, 0x8035, 0xE10B, 0x743F, 0x4A3C,
    0xA74A, 0x94F0, 0x313C, 0x7D2D, 0xFCA4, 0x8195, 0xD551, 0x6EEF, 0x52D6, 0xAEF1,
    0x9000, 0x28EA, 0x7EA2, 0x042F, 0x82D7, 0xCF85, 0x6C12, 0x567C, 0xB23B, 0x8E57,
    0x2634, 0x7EEE, 0x05B1, 0x8305, 0xCF5E, 0x6C57, 0x559C, 0xB0C5, 0x8F86, 0x293E,
    0x7E60, 0x0128, 0x8200, 0xD4DB, 0x6FB0, 0x501C, 0xAAB9, 0x93DC, 0x31DF, 0x7C6D,
    0xF696, 0x8083, 0xE041, 0x754A, 0x4559, 0xA0DB, 0x9C5C, 0x3F8E, 0x77BB, 0xE622,
    0x8025, 0xF1EA, 0x7B7C, 0x3465, 0x94B3, 0xAA90, 0x511A, 0x6E3B, 0xD074, 0x8356,
    0x09E2, 0x7FA6, 0x1C63, 0x88D2, 0xC026, 0x6444, 0x5D75, 0xB736, 0x8D36, 0x274D,
    0x7E39, 0xFD3B, 0x80F8, 0xDE4B, 0x7567, 0x4327, 0x9DA4, 0xA10D, 0x47A6, 0x7309,
    0xD873, 0x81F6, 0x04AC, 0x7F56, 0x1E46, 0x88EE, 0xC151, 0x6618, 0x5A3D, 0xB225,
    0x90ED, 0x3046, 0x7BE3, 0xF070, 0x8003, 0xEE11, 0x7B53, 0x31EE, 0x9190, 0xB1AB,
    0x5A65, 0x655F, 0xBF50, 0x8A4A, 0x231B, 0x7E81, 0xFC66, 0x8098, 0xE42C, 0x7895,
    0x394D, 0x9559, 0xACE0, 0x56A2, 0x67E7, 0xC228, 0x8967, 0x21D3, 0x7E8F, 0xFBCA,
    0x8074, 0xE6AB, 0x79B8, 0x3540, 0x926D, 0xB1DE, 0x5BEF, 0x62CC, 0xBA26, 0x8DA9,
    0x2C8F, 0x7C27, 0xEE9F, 0x800E, 0xF5AB, 0x7DBA, 0x2546, 0x8A35, 0xC1C1, 0x68AD,
    0x5432, 0xA8DF, 0x99BC, 0x420C, 0x73D0, 0xD58F, 0x8394, 0x115F, 0x7FE9, 0x081C,
    0x81B0, 0xDF05, 0x77DD, 0x384E, 0x9305, 0xB2BE, 0x5E39, 0x5F29, 0xB3BC, 0x9287,
    0x37DB, 0x77D4, 0xDE34, 0x81FB, 0x0AE3, 0x7FFE, 0x0C15, 0x8228, 0xDD9F, 0x77CD,
    0x3753, 0x91CE, 0xB5A9, 0x6177, 0x5AEE, 0xADE7, 0x9748, 0x40A5, 0x736D, 0xD254,
    0x851D, 0x19C3, 0x7F09, 0xFA88, 0x8017, 0xF157, 0x7DA0, 0x2225, 0x87A0, 0xCB77,
    0x706A, 0x4573, 0x99F3, 0xAB6F, 0x59A1, 0x61A4, 0xB47D, 0x9386, 0x3C14, 0x74F6,
    0xD44A, 0x84F8, 0x1AC7, 0x7EB1, 0xF65E, 0x8003, 0xF89E, 0x7F05, 0x17FB, 0x8415,
    0xD81D, 0x76DA, 0x36DE, 0x8FFF, 0xBB47, 0x6797, 0x514C, 0xA22E, 0xA389, 0x52ED,
    0x6626, 0xB8E0, 0x91B7, 0x3AA5, 0x74DC, 0xD250, 0x8620, 0x2075, 0x7D5E, 0xECDC,
    0x809E, 0x05E8, 0x7FFE, 0x0717, 0x80B7, 0xEC48, 0x7D5B, 0x1FDF, 0x85B2, 0xD490,
    0x7640, 0x3659, 0x8EB2, 0xBF76, 0x6B94, 0x49F7, 0x9AD0, 0xAD68, 0x5E3E, 0x5A69,
    0xA926, 0x9E96, 0x4F1E, 0x679C, 0xB8DF, 0x92FC, 0x3EFA, 0x71A7, 0xC941, 0x8A71,
    0x2E81, 0x78C4, 0xD9AF, 0x84AD, 0x1E3F, 0x7D45, 0xE9AA, 0x8158, 0x0EA3, 0x7F88,
    0xF8D2, 0x800E, 0x0000, 0x7FF2, 0x06E2, 0x806A, 0xF28D, 0x7EE9, 0x13B0, 0x8208,
    0xE66A, 0x7CCD, 0x1F23, 0x848C, 0xDBA9, 0x79F8, 0x2933, 0x87A0, 0xD24A, 0x76B7,
    0x31E3, 0x8AFA, 0xCA46, 0x7352, 0x393F, 0x8E5B, 0xC38E, 0x7003, 0x3F57, 0x918C,
    0xBE10, 0x6CFB, 0x443E, 0x9463, 0xB9BB, 0x6A60, 0x4807, 0x96BB, 0xB67B, 0x6850,
    0x4AC1, 0x987C, 0xB443, 0x66E2, 0x4C7A, 0x9993, 0xB306, 0x6624, 0x4D3B, 0x99F7,
    0xB2C0, 0x661D, 0x4D08, 0x99A2, 0xB36D, 0x66CD, 0x4BDF, 0x9898, 0xB513, 0x682D,
    0x49BB, 0x96E4, 0xB7B8, 0x6A31, 0x4691, 0x9497, 0xBB6B, 0x6CC2, 0x4252, 0x91CA,
    0xC03B, 0x6FC3, 0x3CEC, 0x8E9E, 0xC63B, 0x730E, 0x364E, 0x8B3F, 0xCD7C, 0x7673,
    0x2E65, 0x87E2, 0xD611, 0x79B9, 0x2521, 0x84C6, 0xE005, 0x7C9A, 0x1A7C, 0x8234,
    0xEB5C, 0x7EC7, 0x0E75, 0x8080, 0xF80F, 0x7FEA, 0x011B, 0x8007, 0x0607, 0x7FA0,
    0xF28F, 0x812C, 0x151B, 0x7D86, 0xE304, 0x8455, 0x2508, 0x7937, 0xD2CC, 0x89E4,
    0x3571, 0x7251, 0xC252, 0x9234, 0x45DA, 0x6884, 0xB221, 0x9D8E, 0x55A7, 0x5B92,
    0xA2E5, 0xAC1E, 0x6420, 0x4B61, 0x9564, 0xBDEC, 0x7073, 0x3802, 0x8A79, 0xD2CB,
    0x79BB, 0x21BD, 0x830E, 0xEA54, 0x7F0F, 0x091C, 0x8009, 0x03D6, 0x7F92, 0xEEF5,
    0x8238, 0x1E5B, 0x7A87, 0xD463, 0x8A3F, 0x38A0, 0x6F6D, 0xBACE, 0x9877, 0x511E,
    0x5E18, 0xA3D4, 0xACD8, 0x6622, 0x46CC, 0x9139, 0xC6DE, 0x75E2, 0x2A52, 0x84C1,
    0xE574, 0x7EAB, 0x0A0A, 0x8004, 0x06EE, 0x7F0D, 0xE7ED, 0x843B, 0x2910, 0x7614,
    0xC674, 0x9207, 0x4927, 0x6381, 0xA87F, 0xA93A, 0x6438, 0x47F7, 0x9112, 0xC8B0,
    0x774A, 0x2522, 0x8303, 0xEE35, 0x7FC1, 0xFDBC, 0x809C, 0x1691, 0x7BC3, 0xD56C,
    0x8B2E, 0x3DBC, 0x6A9E, 0xB089, 0xA2B2, 0x5F33, 0x4D22, 0x939E, 0xC588, 0x7683,
    0x25CB, 0x82DC, 0xF055, 0x7FEC, 0xF8C2, 0x8164, 0x1E37, 0x7916, 0xCB8A, 0x909F,
    0x492F, 0x61AB, 0xA46B, 0xAFB2, 0x6AE4, 0x3BCA, 0x8993, 0xDB37, 0x7D9C, 0x0C1A,
    0x8002, 0x0D59, 0x7D51, 0xD972, 0x8A7E, 0x3E76, 0x68B8, 0xABFE, 0xA8AD, 0x662E,
    0x41F0, 0x8BF4, 0xD6A0, 0x7CD8, 0x0EAB, 0x8002, 0x0D01, 0x7D28, 0xD7A5, 0x8BB8,
    0x4209, 0x659C, 0xA74A, 0xAE4C, 0x6B21, 0x396A, 0x87CC, 0xE21D, 0x7F13, 0x007F,
    0x80D2, 0x1D36, 0x7850, 0xC668, 0x955A, 0x52FF, 0x56C6, 0x9822, 0xC257, 0x76D5,
    0x20A8, 0x812B, 0xFE97, 0x7F2C, 0xE1CB, 0x8862, 0x3C39, 0x686D, 0xA955, 0xADA2,
    0x6BB7, 0x36B4, 0x8630, 0xE8DB, 0x7FD4, 0xF5BC, 0x82E1, 0x2B42, 0x71A8, 0xB684,
    0xA1FC, 0x62B4, 0x4369, 0x8B10, 0xDC60, 0x7EA7, 0x00E9, 0x811B, 0x2229, 0x7567,
    0xBD20, 0x9D53, 0x5E99, 0x47FA, 0x8D04, 0xD8BD, 0x7E30, 0x0312, 0x80F0, 0x21A8,
    0x7548, 0xBC2C, 0x9E92, 0x6070, 0x44FC, 0x8B26, 0xDDBE, 0x7F0F, 0xFC36, 0x8218,
    0x29C9, 0x713D, 0xB3C9, 0xA609, 0x67C5, 0x3A0C, 0x8652, 0xEBA9, 0x7FFE, 0xEC64,
    0x8629, 0x39EB, 0x678D, 0xA54B, 0xB54C, 0x7289, 0x2606, 0x8142, 0x02D9, 0x7DCF,
    0xD44A, 0x9074, 0x5031, 0x5537, 0x93BF, 0xCE93, 0x7CA3, 0x07EF, 0x80BA, 0x22B8,
    0x7396, 0xB648, 0xA562, 0x687F, 0x36FC, 0x84B5, 0xF355, 0x7FA4, 0xE093, 0x8B44,
    0x4805, 0x5B98, 0x97EC, 0xC8F8, 0x7B75, 0x0B61, 0x8085, 0x21FA, 0x7357, 0xB4BA,
    0xA7B7, 0x6B16, 0x318F, 0x82F4, 0xFBF1, 0x7E84, 0xD5BD, 0x9105, 0x5325, 0x503E,
    0x8F1F, 0xD9BE, 0x7F24, 0xF6B1, 0x845F, 0x37D9, 0x6687, 0xA154, 0xBD72, 0x7805,
    0x14AE, 0x8011, 0x1C80, 0x74EE, 0xB648, 0xA7AE, 0x6C12, 0x2E25, 0x81E3, 0x0359,
    0x7CC8, 0xCB65, 0x980F, 0x5DDD, 0x428E, 0x8792, 0xEDAE, 0x7FC6, 0xDEDD, 0x8DA0,
    0x4F75, 0x5217, 0x8F1F, 0xDC07, 0x7F9A, 0xEF90, 0x872F, 0x4255, 0x5D54, 0x96EB,
    0xCE71, 0x7DC3, 0xFCE6, 0x838E, 0x377D, 0x6502, 0x9DC4, 0xC4B3, 0x7B75, 0x069E,
    0x81BA, 0x2F8C, 0x69CF, 0xA2D5, 0xBE7D, 0x798E, 0x0CAB, 0x80F0, 0x2AD8, 0x6C47,
    0xA59B, 0xBB8B, 0x789B, 0x0F11, 0x80BA, 0x298E, 0x6CB9, 0xA5D6, 0xBBB6, 0x78D8,
    0x0DD5, 0x80EC, 0x2BB6, 0x6B37, 0xA380, 0xBF00, 0x7A37, 0x08F4, 0x81AF, 0x313F,
    0x678D, 0x9ED0, 0xC594, 0x7C5C, 0x0068, 0x8378, 0x39F6, 0x6148, 0x983B, 0xCFB9,
    0x7E9A, 0xF437, 0x8705, 0x4572, 0x57C9, 0x9086, 0xDDBE, 0x7FF2, 0xE48C, 0x8D58,
    0x5301, 0x4A53, 0x88D3, 0xEFD7, 0x7F10, 0xD1DF, 0x979F, 0x6186, 0x3839, 0x82AC,
    0x05ED, 0x7A5D, 0xBD20, 0xA70C, 0x6F61, 0x2116, 0x8002, 0x1F65, 0x701F, 0xA7E0,
    0xBC97, 0x7A60, 0x0510, 0x830F, 0x3ADD, 0x5EBD, 0x9476, 0xD8AA, 0x7FD4, 0xE536,
    0x8E15, 0x55F9, 0x4523, 0x85F7, 0xFAB0, 0x7CCD, 0xC3C7, 0xA2EB, 0x6D4F, 0x234B,
    0x8003, 0x20A4, 0x6E9A, 0xA469, 0xC257, 0x7C95, 0xFAD4, 0x8638, 0x46C5, 0x5390,
    0x8C0B, 0xEB4D, 0x7F2E, 0xCF7B, 0x9B4E, 0x678B, 0x2BFA, 0x8058, 0x1A39, 0x7130,
    0xA74A, 0xBFE9, 0x7C3A, 0xFB15, 0x8689, 0x48A9, 0x50D7, 0x8A16, 0xF155, 0x7E24,
    0xC79D, 0xA1B5, 0x6DB4, 0x201D, 0x8015, 0x28A9, 0x68B8, 0x9B8A, 0xD0CA, 0x7F83,
    0xE5F4, 0x8F81, 0x5AEC, 0x3BF1, 0x8264, 0x0CED, 0x7613, 0xAE53, 0xB999, 0x7AD0,
    0xFE78, 0x861C, 0x492F, 0x4EC4, 0x8859, 0xF7FD, 0x7C60, 0xBE35, 0xAAC3, 0x748E,
    0x0FAB, 0x821A, 0x3BBF, 0x5A06, 0x8E25, 0xEA93, 0x7EC4, 0xC8CA, 0xA2B2, 0x6FD1,
    0x1951, 0x80CA, 0x344C, 0x5F39, 0x9168, 0xE4A3, 0x7F64, 0xCCEF, 0xA022, 0x6E4B,
    0x1B95, 0x80A0, 0x338B, 0x5F46, 0x9112, 0xE605, 0x7F2A, 0xCA48, 0xA297, 0x7075,
    0x168A, 0x8156, 0x398C, 0x5A30, 0x8D3E, 0xEEC4, 0x7DB6, 0xC10F, 0xAA87, 0x75A2,
    0x0A0A, 0x83F1, 0x45C4, 0x4F13, 0x8734, 0xFF0D, 0x7963, 0xB232, 0xB934, 0x7BE1,
    0xF600, 0x8AAE, 0x56C4, 0x3C6D, 0x8194, 0x16B9, 0x6F6D, 0x9FC2, 0xD035, 0x7FDD,
    0xDAFF, 0x98BE, 0x69B3, 0x20CC, 0x806E, 0x3481, 0x5C61, 0x8D89, 0xF08D, 0x7CD7,
    0xBB4B, 0xB195, 0x79BB, 0xFBF2, 0x890D, 0x54E5, 0x3D23, 0x8170, 0x194D, 0x6D3A,
    0x9BE0, 0xD780, 0x7FF1, 0xD06D, 0xA0E4, 0x713E, 0x10C4, 0x832A, 0x45DA, 0x4C44,
    0x8515, 0x0970, 0x744D, 0xA53C, 0xCB4B, 0x7FB8, 0xDAF8, 0x9A5F, 0x6CA6, 0x18EB,
    0x81C2, 0x4078, 0x507F, 0x8660, 0x0607, 0x754D, 0xA648, 0xCAD6, 0x7FBF, 0xD998,
    0x9BDA, 0x6E65, 0x14A4, 0x82BE, 0x45D1, 0x4ABB, 0x8411, 0x0F30, 0x70DF, 0x9EB1,
    0xD611, 0x7FE4, 0xCC75, 0xA5DE, 0x759B, 0x03C7, 0x87A5, 0x54D6, 0x39C5, 0x8085,
    0x2484, 0x6468, 0x9106, 0xEE0D, 0x7C4E, 0xB559, 0xBB6B, 0x7DDF, 0xE664, 0x9558,
    0x69A2, 0x1B41, 0x81E2, 0x43CA, 0x4AED, 0x839A, 0x133D, 0x6DCA, 0x9970, 0xE031,
    0x7EC0, 0xBF32, 0xB2C0, 0x7BD7, 0xEE71, 0x91A6, 0x6643, 0x1FB8, 0x8159, 0x41EA,
    0x4BBD, 0x838E, 0x149A, 0x6C71, 0x973A, 0xE506, 0x7DBF, 0xB8F7, 0xB9BB, 0x7DF1,
    0xE3B1, 0x9847, 0x6DB4, 0x117C, 0x8491, 0x4FC9, 0x3C72, 0x8079, 0x2878, 0x5F6F,
    0x8BD4, 0xFCE2, 0x76A0, 0xA4A1, 0xD24A, 0x7FDC, 0xC772, 0xAD77, 0x7ABA, 0xEFF8,
    0x9232, 0x686E, 0x1996, 0x82F1, 0x4B81, 0x3FEA, 0x80B7, 0x2764, 0x5F3E, 0x8B20,
    0x0000, 0x74D8, 0xA08F, 0xD93F, 0x7F27, 0xBE7A, 0xB6AE, 0x7DC9, 0xE1C1, 0x9B2D,
    0x7173, 0x070B, 0x88C1, 0x5BC1, 0x2B19, 0x8078, 0x3EFA, 0x4B0D, 0x8276, 0x1DC7,
    0x649D, 0x8E05, 0xFAF0, 0x7633, 0xA1C2, 0xD91D, 0x7EF9, 0xBBCC, 0xBAA7, 0x7ED1,
    0xD9FC, 0xA171, 0x7640, 0xFA10, 0x8ED6, 0x6654, 0x19DD, 0x839D, 0x507C, 0x3775,
    0x8002, 0x3663, 0x513A, 0x83C1, 0x19CD, 0x65F7, 0x8E2D, 0xFC75, 0x74DC, 0x9E48,
    0xDFF3, 0x7D88, 0xB2E0, 0xC5A9, 0x7FF7, 0xCAA3, 0xAEB4, 0x7C79, 0xE43E, 0x9BE8,
    0x73A3, 0xFE69, 0x8DCC, 0x663A, 0x17FB, 0x849E, 0x5522, 0x2FF9, 0x805E, 0x414F,
    0x4591, 0x80D4, 0x2BB6, 0x5829, 0x859A, 0x1540, 0x6758, 0x8E2D, 0xFEC5, 0x72E6,
    0x99F3, 0xE8FB, 0x7AC4, 0xA846, 0xD47F, 0x7F08, 0xB882, 0xC1CB, 0x7FE9, 0xCA03,
    0xB139, 0x7DB1, 0xDC34, 0xA303, 0x78BB, 0xEE8D, 0x9748, 0x716D, 0x009A, 0x8E0D,
    0x6831, 0x11FB, 0x8744, 0x5D70, 0x2261, 0x82CC, 0x518E, 0x3192, 0x8078, 0x44EB,
    0x3F65, 0x8014, 0x37DB, 0x4BC3, 0x8163, 0x2AAA, 0x56A1, 0x8428, 0x1D98, 0x6001,
    0x8823, 0x10DB, 0x67F1, 0x8D17, 0x049D, 0x6E82, 0x92CA, 0xF901, 0x73D0, 0x9906,
    0xEE1D, 0x77F7, 0x9F99, 0xE402, 0x7B19, 0xA657, 0xDABA, 0x7D55, 0xAD19, 0xD248,
    0x7ECF, 0xB3BD, 0xCAAA, 0x7FA6, 0xBA26, 0xC3DD, 0x7FFA, 0xC03D, 0xBDD9, 0x7FE9,
    0xC5EE, 0xB895, 0x7F8C, 0xCB27, 0xB407, 0x7EFE, 0xCFDD, 0xB023, 0x7E53, 0xD405,
    0xACE0, 0x7D9D, 0xD797, 0xAA33, 0x7CEF, 0xDA8E, 0xA814, 0x7C53, 0xDCE5, 0xA67B,
    0x7BD6, 0xDE9A, 0xA562, 0x7B7F, 0xDFA9, 0xA4C5, 0x7B53, 0xE013, 0xA4A1, 0x7B54,
    0xDFD6, 0xA4F5, 0x7B83, 0xDEF3, 0xA5C3, 0x7BDD, 0xDD6B, 0xA70E, 0x7C5D, 0xDB3F,
    0xA8DC, 0x7CF9, 0xD873, 0xAB32, 0x7DA9, 0xD50A, 0xAE1A, 0x7E5E, 0xD109, 0xB19B,
    0x7F08, 0xCC79, 0xB5C2, 0x7F94, 0xC762, 0xBA97, 0x7FEC, 0xC1D0, 0xC026, 0x7FF8,
    0xBBD3, 0xC679, 0x7F9D, 0xB57D, 0xCD98, 0x7EBC, 0xAEE6, 0xD58A, 0x7D37, 0xA829,
    0xDE51, 0x7AEC, 0xA167, 0xE7EE, 0x77BB, 0x9AC4, 0xF25B, 0x7382, 0x946C, 0xFD8B,
    0x6E20, 0x8E8F, 0x096A, 0x6779, 0x8962, 0x15DF, 0x5F72, 0x851E, 0x22C4, 0x55F9,
    0x8200, 0x2FE9, 0x4B02, 0x8046, 0x3D15, 0x3E8C, 0x802F, 0x4A03, 0x30A2, 0x81F8,
    0x5664, 0x215C, 0x85D7, 0x61DF, 0x10E4, 0x8BFE, 0x6C12, 0xFF76, 0x948E, 0x7496,
    0xED60, 0x9F9C, 0x7B01, 0xDB05, 0xAD2A, 0x7EEC, 0xC8DC, 0xBD1E, 0x7FF3, 0xB76B,
    0xCF46, 0x7DC1, 0xA74A, 0xE352, 0x7813, 0x991B, 0xF8D0, 0x6EBF, 0x8D85, 0x0F2C,
    0x61BC, 0x852D, 0x25B7, 0x5128, 0x80AA, 0x3BA2, 0x3D4F, 0x807F, 0x5007, 0x26AE,
    0x850F, 0x61F3, 0x0DF3, 0x8E8F, 0x7072, 0xF403, 0x9CFB, 0x7A98, 0xD9EC, 0xB010,
    0x7F96, 0xC0E5, 0xC743, 0x7ECA, 0xAA3B, 0xE1BB, 0x77D0, 0x9745, 0xFE56, 0x6A91,
    0x894A, 0x1BAE, 0x5758, 0x816B, 0x3829, 0x3ED2, 0x8089, 0x520A, 0x221D, 0x872A,
    0x678D, 0x02BA, 0x9562, 0x7709, 0xE285, 0xAABD, 0x7F16, 0xC39B, 0xC63B, 0x7EAE,
    0xA83A, 0xE648, 0x7554, 0x9298, 0x08D0, 0x6332, 0x84AD, 0x2B55, 0x492A, 0x8003,
    0x4B1B, 0x28DF, 0x8582, 0x655E, 0x04A5, 0x9544, 0x7795, 0xDF64, 0xAE7D, 0x7FB5,
    0xBC5B, 0xCF67, 0x7C75, 0x9EE5, 0xF55B, 0x6D8C, 0x8A1A, 0x1CF4, 0x53D2, 0x8077,
    0x4257, 0x3153, 0x8389, 0x6191, 0x0932, 0x939B, 0x7704, 0xDF77, 0xAF95, 0x7FDE,
    0xB8AA, 0xD4E7, 0x7A87, 0x995A, 0xFFB6, 0x66F4, 0x858E, 0x2B2F, 0x46D4, 0x8032,
    0x520B, 0x1D8D, 0x8A98, 0x6F33, 0xEFF6, 0xA41C, 0x7E71, 0xC3D0, 0xCA0B, 0x7D24,
    0x9F1C, 0xF7C8, 0x6AC5, 0x873C, 0x2746, 0x4931, 0x801E, 0x51CC, 0x1CA2, 0x8B7E,
    0x70E1, 0xEB43, 0xA866, 0x7F5E, 0xBC67, 0xD31A, 0x7A59, 0x977F, 0x0566, 0x61DA,
    0x82DB, 0x3774, 0x3920, 0x8282, 0x60EF, 0x065E, 0x9748, 0x7A75, 0xD1EA, 0xBE61,
    0x7EF9, 0xA4ED, 0xF18B, 0x6CE6, 0x87CA, 0x27EA, 0x46B9, 0x8073, 0x5781, 0x12E2,
    0x9115, 0x76FF, 0xDAD9, 0xB750, 0x7FB1, 0xA979, 0xEC52, 0x6F0F, 0x88EB, 0x25E1,
    0x47A1, 0x8072, 0x583A, 0x10DC, 0x92A8, 0x7875, 0xD5ED, 0xBC84, 0x7EFC, 0xA389,
    0xF59B, 0x6988, 0x8534, 0x319C, 0x3C09, 0x827B, 0x62DC, 0x003E, 0x9CE0, 0x7D7C,
    0xC3CE, 0xCF0A, 0x7A67, 0x953E, 0x0D8B, 0x5973, 0x8070, 0x494E, 0x21ED, 0x8B65,
    0x7325, 0xE143, 0xB443, 0x7FBF, 0xA7F4, 0xF143, 0x6AED, 0x8562, 0x32BD, 0x394A,
    0x838B, 0x670D, 0xF791, 0xA3E2, 0x7F56, 0xB799, 0xDE50, 0x73F1, 0x8B9B, 0x22DE,
    0x4724, 0x80E1, 0x5DE2, 0x0521, 0x9B80, 0x7D94, 0xC106, 0xD481, 0x77A2, 0x8F77,
    0x1B46, 0x4CDB, 0x804E, 0x5A27, 0x09AA, 0x993C, 0x7CFC, 0xC2D8, 0xD351, 0x77CA,
    0x8F49, 0x1C72, 0x4B3B, 0x8088, 0x5CB7, 0x0531, 0x9C7C, 0x7E29, 0xBCD6, 0xDAAC,
    0x7480, 0x8B23, 0x2651, 0x4206, 0x8227, 0x64FE, 0xF7B1, 0xA61A, 0x7FD4, 0xAFCC,
    0xEB03, 0x6C20, 0x84DB, 0x3830, 0x3016, 0x879E, 0x70D2, 0xE172, 0xB821, 0x7EC8,
    0x9DF6, 0x04BB, 0x5BA3, 0x8040, 0x5007, 0x141C, 0x94F7, 0x7BF6, 0xC407, 0xD4EE,
    0x7606, 0x8BC9, 0x26F4, 0x3F85, 0x8331, 0x695C, 0xEE1F, 0xAEEA, 0x7FC5, 0xA3C1,
    0xFD7D, 0x5F9C, 0x8098, 0x4DAB, 0x15AA, 0x94E1, 0x7C45, 0xC1AD, 0xD8CF, 0x73C8,
    0x890E, 0x2ED1, 0x36DE, 0x8624, 0x6FFE, 0xE061, 0xBB6B, 0x7DAC, 0x9812, 0x111F,
    0x5058, 0x806A, 0x5F3B, 0xFC6A, 0xA5C3, 0x7FF7, 0xA9B4, 0xF734, 0x6266, 0x80D5,
    0x4D78, 0x13EC, 0x96FE, 0x7D88, 0xBAF9, 0xE244, 0x6E40, 0x84A5, 0x3D2F, 0x263A,
    0x8DAC, 0x78E9, 0xC9E1, 0xD293, 0x756E, 0x8993, 0x2FF5, 0x3360, 0x8845, 0x7418,
    0xD537, 0xC7E1, 0x7963, 0x8DEF, 0x26AD, 0x3BB8, 0x857B, 0x7077, 0xDC54, 0xC1C8,
    0x7B3B, 0x90A0, 0x21CC, 0x3FA8, 0x8469, 0x6EDB, 0xDEEF, 0xBFF3, 0x7BA1, 0x9113,
    0x217E, 0x3F69, 0x84A4, 0x6F96, 0xDCEF, 0xC247, 0x7ABE, 0x8F33, 0x25C7, 0x3AF8,
    0x8645, 0x7283, 0xD667, 0xC8E6, 0x7839, 0x8B60, 0x2E7F, 0x3213, 0x89E5, 0x7702,
    0xCB98, 0xD42A, 0x733B, 0x8680, 0x3B3F, 0x2456, 0x9093, 0x7BE7, 0xBD1B, 0xE478,
    0x6A83, 0x8206, 0x4B33, 0x1168, 0x9BB8, 0x7F72, 0xAC0C, 0xFA07, 0x5C8C, 0x8002,
    0x5CE3, 0xF94F, 0xACE0, 0x7F49, 0x9A50, 0x147A, 0x47DD, 0x830C, 0x6DF5, 0xDCD4,
    0xC555, 0x78A3, 0x8AC0, 0x327A, 0x2B81, 0x8E06, 0x7B0F, 0xBE01, 0xE58E, 0x68A9,
    0x812D, 0x5137, 0x07B1, 0xA38E, 0x7FFA, 0xA07D, 0x0C6B, 0x4D32, 0x820F, 0x6C2A,
    0xDE9F, 0xC513, 0x7834, 0x89A4, 0x367F, 0x25D7, 0x91A7, 0x7D40, 0xB519, 0xF1A2,
    0x601E, 0x8005, 0x5D90, 0xF534, 0xB285, 0x7DC7, 0x92B0, 0x24B1, 0x36B4, 0x89FB,
    0x78EE, 0xC1EC, 0xE39D, 0x6858, 0x80CC, 0x557B, 0xFF8A, 0xAB44, 0x7F10, 0x96BD,
    0x1E73, 0x3B9F, 0x884D, 0x77B7, 0xC433, 0xE209, 0x68B8, 0x80C3, 0x5670, 0xFD47,
    0xADB7, 0x7E7D, 0x93E3, 0x2460, 0x353E, 0x8B66, 0x7A9E, 0xBB88, 0xECD1, 0x6165,
    0x8002, 0x6029, 0xEE77, 0xBA72, 0x7AD6, 0x8B71, 0x35E6, 0x22C0, 0x956A, 0x7F0C,
    0xA995, 0x0457, 0x4FC3, 0x825B, 0x6F79, 0xD3DB, 0xD3D7, 0x6F69, 0x8246, 0x5073,
    0x02DD, 0xAB3B, 0x7EA2, 0x932B, 0x27DF, 0x2FC1, 0x8F0F, 0x7D3C, 0xB0FD, 0xFBF9,
    0x5523, 0x8165, 0x6D47, 0xD6AF, 0xD24A, 0x6F90, 0x8216, 0x5247, 0xFF27, 0xAF16,
    0x7D8B, 0x8F4B, 0x3066, 0x25EE, 0x9512, 0x7F48, 0xA624, 0x0BC1, 0x479C, 0x856B,
    0x7640, 0xC34D, 0xE7EB, 0x6201, 0x8006, 0x64B4, 0xE382, 0xC7A4, 0x7414, 0x83CF,
    0x4D38, 0x03E7, 0xACC1, 0x7DCB, 0x8F1C, 0x3259, 0x2242, 0x9837, 0x7FD7, 0x9FFA,
    0x1658, 0x3D02, 0x8A38, 0x7B65, 0xB477, 0xFB0C, 0x5340, 0x8267, 0x71DB, 0xCACC,
    0xE1C7, 0x64A6, 0x8001, 0x64B2, 0xE17D, 0xCB68, 0x714F, 0x820E, 0x5546, 0xF765,
    0xB85F, 0x79A6, 0x8780, 0x44C9, 0x0BB3, 0xA8C4, 0x7E4B, 0x8F4F, 0x3436, 0x1DE7,
    0x9C71, 0x7FF4, 0x988B, 0x244D, 0x2DBF, 0x9311, 0x7F5E, 0xA264, 0x1598, 0x3B2D,
    0x8C3A, 0x7D39, 0xAC31, 0x0873, 0x4645, 0x8775, 0x7A28, 0xB56A, 0xFD15, 0x4F33,
    0x844E, 0x76B4, 0xBDA9, 0xF396, 0x562C, 0x8258, 0x7350, 0xC4A5, 0xEC01, 0x5B68,
    0x8137, 0x7055, 0xCA2A, 0xE650, 0x5F1C, 0x809F, 0x6E05, 0xCE16, 0xE27D, 0x6172,
    0x805A, 0x6C91, 0xD054, 0xE07F, 0x6287, 0x8043,
};