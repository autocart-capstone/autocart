#include <stddef.h> // for size_t
#include <stdint.h> // for uint16_t

#define SOUND_SAMPLES_LEN 4096

//These are actually signed ints 
const uint16_t sound_samples[SOUND_SAMPLES_LEN] = {
    0xC003, 0xFFF6, 0x4013, 0x9113, 0x7FFE, 0x9157, 0x3F90, 0x00A7, 0xBF4A, 0x6F5B,
    0x8003, 0x6E1A, 0xC182, 0xFDFF, 0x41FA, 0x8FDE, 0x7FF6, 0x92D9, 0x3CC6, 0x0416,
    0xBC24, 0x713D, 0x801F, 0x6BC9, 0xC59E, 0xF918, 0x4657, 0x8D5E, 0x7FB5, 0x960A,
    0x374E, 0x0A75, 0xB69D, 0x7447, 0x809E, 0x67A3, 0xCC7C, 0xF145, 0x4CF6, 0x89E6,
    0x7ED7, 0x9B3E, 0x2EFC, 0x13B8, 0xAEFC, 0x7809, 0x81FE, 0x6142, 0xD650, 0xE69B,
    0x557D, 0x8603, 0x7CC9, 0xA2ED, 0x239B, 0x1FBC, 0xA5B2, 0x7BDC, 0x84ED, 0x5823,
    0xE348, 0xD94F, 0x5F5F, 0x8277, 0x78C5, 0xADA0, 0x1504, 0x2E37, 0x9B6C, 0x7EE1,
    0x8A3F, 0x4BB8, 0xF380, 0xC9C6, 0x69CC, 0x8041, 0x71E6, 0xBBE4, 0x0332, 0x3EA2,
    0x911E, 0x7FFB, 0x92E9, 0x3B7F, 0x06DC, 0xB8B2, 0x73AB, 0x8096, 0x6735, 0xCE27,
    0xEE65, 0x501B, 0x880A, 0x7DDF, 0x9FDD, 0x2727, 0x1CF2, 0xA726, 0x7B8E, 0x84D4,
    0x57C9, 0xE493, 0xD741, 0x6158, 0x81C6, 0x7724, 0xB1EC, 0x0EB9, 0x34D9, 0x96A8,
    0x7FBE, 0x8E63, 0x42F8, 0xFEDD, 0xBEF7, 0x7096, 0x8025, 0x6A70, 0xC98D, 0xF2CE,
    0x4D11, 0x8937, 0x7E54, 0x9E82, 0x288F, 0x1C15, 0xA75C, 0x7BA2, 0x8513, 0x56B3,
    0xE69C, 0xD4BA, 0x636F, 0x8131, 0x7571, 0xB5FB, 0x091C, 0x3A75, 0x92EF, 0x7FFE,
    0x924C, 0x3B7D, 0x080E, 0xB6BB, 0x7526, 0x8120, 0x6396, 0xD4CA, 0xE634, 0x5749,
    0x84BC, 0x7B2E, 0xA8F8, 0x1961, 0x2BBB, 0x9BF8, 0x7EFF, 0x8B53, 0x4814, 0xF9B9,
    0xC29F, 0x6EFF, 0x800F, 0x6B33, 0xC927, 0xF24F, 0x4E36, 0x8859, 0x7DC0, 0xA153,
    0x2397, 0x220B, 0xA263, 0x7D77, 0x87DF, 0x4F28, 0xF152, 0xC9D5, 0x6AF2, 0x8010,
    0x6EE2, 0xC32F, 0xF8A2, 0x4961, 0x8A79, 0x7EA2, 0x9E0F, 0x27FE, 0x1DEB, 0xA519,
    0x7CB6, 0x86CC, 0x5164, 0xEED1, 0xCBCF, 0x69EE, 0x801D, 0x6F71, 0xC27E, 0xF911,
    0x494E, 0x8A5E, 0x7E8B, 0x9EAD, 0x26C1, 0x1F85, 0xA3B4, 0x7D38, 0x87B1, 0x4F06,
    0xF22E, 0xC86C, 0x6C2B, 0x8002, 0x6D04, 0xC70A, 0xF39C, 0x4E00, 0x8813, 0x7D66,
    0xA346, 0x1FD2, 0x26CA, 0x9E67, 0x7EAB, 0x8AE6, 0x47CB, 0xFB74, 0xBFE5, 0x712D,
    0x805C, 0x670A, 0xD120, 0xE857, 0x56F7, 0x8465, 0x7A52, 0xAC87, 0x12F7, 0x3363,
    0x960C, 0x7FEC, 0x917F, 0x3B08, 0x0AA6, 0xB2F0, 0x77B7, 0x8298, 0x5C5A, 0xE142,
    0xD79C, 0x630B, 0x80F5, 0x73B0, 0xBB88, 0x0000, 0x447C, 0x8C47, 0x7F05, 0x9D2A,
    0x27E8, 0x1F75, 0xA2F5, 0x7DA9, 0x88E2, 0x4B6C, 0xF7D2, 0xC25F, 0x7035, 0x8046,
    0x674E, 0xD173, 0xE737, 0x5862, 0x83B6, 0x793C, 0xAFDD, 0x0DDF, 0x38C4, 0x926B,
    0x7FF4, 0x95EE, 0x32CB, 0x147E, 0xAAA8, 0x7B4C, 0x85A3, 0x52CE, 0xEEEA, 0xC9F3,
    0x6C1D, 0x8002, 0x6B5D, 0xCB46, 0xED5F, 0x5419, 0x8518, 0x7AB7, 0xAC71, 0x11D7,
    0x3590, 0x940D, 0x7FFE, 0x94B6, 0x3465, 0x1335, 0xAB4B, 0x7B31, 0x85A6, 0x526D,
    0xEFDB, 0xC8B0, 0x6D18, 0x800A, 0x69D7, 0xCE34, 0xE9C5, 0x5724, 0x83E7, 0x7934,
    0xB0A5, 0x0BFB, 0x3B42, 0x908E, 0x7FC1, 0x991A, 0x2CDC, 0x1BA9, 0xA4BA, 0x7D6D,
    0x88F0, 0x4A35, 0xFAAA, 0xBEBA, 0x72C5, 0x80E8, 0x6239, 0xDA83, 0xDC94, 0x60DB,
    0x812A, 0x739A, 0xBD3A, 0xFC35, 0x4925, 0x8950, 0x7D90, 0xA481, 0x1B92, 0x2D5E,
    0x987E, 0x7FD7, 0x919F, 0x38CF, 0x0F5E, 0xAD78, 0x7AAB, 0x8566, 0x5253, 0xF0FC,
    0xC6C4, 0x6EB4, 0x8034, 0x66DD, 0xD3EC, 0xE2C5, 0x5CEE, 0x81FB, 0x758F, 0xB9B0,
    0xFFD8, 0x4697, 0x8A49, 0x7DEE, 0xA383, 0x1C6D, 0x2D10, 0x985C, 0x7FE0, 0x924D,
    0x371D, 0x11C8, 0xAB35, 0x7BA2, 0x86A2, 0x4EB7, 0xF628, 0xC1AF, 0x71BB, 0x80C5,
    0x624A, 0xDB79, 0xDA8E, 0x62ED, 0x80A8, 0x712C, 0xC2E2, 0xF497, 0x5024, 0x85FC,
    0x7AFB, 0xAD53, 0x0E9A, 0x3A65, 0x9038, 0x7F97, 0x9B87, 0x2787, 0x22BF, 0x9EAC,
    0x7F1C, 0x8DFC, 0x3E70, 0x0A3D, 0xB087, 0x79DC, 0x84F7, 0x5293, 0xF1DB, 0xC4E9,
    0x7051, 0x8089, 0x635E, 0xDA79, 0xDAEE, 0x6317, 0x8091, 0x706E, 0xC4D9, 0xF1B9,
    0x52DD, 0x84C8, 0x798D, 0xB199, 0x0879, 0x405D, 0x8CC7, 0x7EB0, 0xA131, 0x1E77,
    0x2C54, 0x980D, 0x7FF1, 0x93F4, 0x3310, 0x1777, 0xA60B, 0x7D89, 0x8A0E, 0x45C3,
    0x0272, 0xB62B, 0x77CA, 0x838E, 0x562A, 0xEDDE, 0xC7D2, 0x6F18, 0x8063, 0x63FE,
    0xDA3F, 0xDA6F, 0x63E5, 0x8064, 0x6F12, 0xC804, 0xED74, 0x56A8, 0x8356, 0x7755,
    0xB785, 0x0064, 0x47DA, 0x88ED, 0x7CCD, 0xA902, 0x12D1, 0x37F1, 0x90D3, 0x7F91,
    0x9CA7, 0x245D, 0x275D, 0x9AAD, 0x7FCB, 0x928B, 0x34B9, 0x1686, 0xA61D, 0x7DAE,
    0x8AB2, 0x43AC, 0x05C8, 0xB2C7, 0x797A, 0x8512, 0x510A, 0xF574, 0xC052, 0x7370,
    0x8194, 0x5CB7, 0xE5CA, 0xCE6A, 0x6BD8, 0x8016, 0x66A7, 0xD704, 0xDCC4, 0x62F7,
    0x806F, 0x6ED9, 0xC949, 0xEB1D, 0x5914, 0x826F, 0x7555, 0xBCB9, 0xF939, 0x4E6F,
    0x85E4, 0x7A2F, 0xB168, 0x06E6, 0x4347, 0x8A9A, 0x7D7F, 0xA75D, 0x13FF, 0x37D3,
    0x905D, 0x7F63, 0x9E9C, 0x2064, 0x2C44, 0x96FB, 0x7FFE, 0x971D, 0x2BFC, 0x20C7,
    0x9E42, 0x7F75, 0x90D5, 0x36B9, 0x1581, 0xA606, 0x7DEB, 0x8BB3, 0x4091, 0x0A90,
    0xAE1D, 0x7B88, 0x87A3, 0x4981, 0x000F, 0xB662, 0x786F, 0x848D, 0x518B, 0xF610,
    0xBEB2, 0x74C3, 0x8258, 0x58B5, 0xECA2, 0xC6F2, 0x70A7, 0x80EC, 0x5F07, 0xE3CE,
    0xCF07, 0x6C39, 0x802E, 0x648E, 0xDB9C, 0xD6DC, 0x6796, 0x8004, 0x6957, 0xD40D,
    0xDE60, 0x62D7, 0x8056, 0x6D72, 0xCD22, 0xE584, 0x5E15, 0x810C, 0x70EE, 0xC6D7,
    0xEC3E, 0x5963, 0x820F, 0x73DB, 0xC12A, 0xF283, 0x54D4, 0x834C, 0x7649, 0xBC14,
    0xF84E, 0x5078, 0x84AE, 0x7847, 0xB78F, 0xFD9B, 0x4C5C, 0x8624, 0x79E5, 0xB394,
    0x0265, 0x488B, 0x879F, 0x7B30, 0xB01B, 0x06AC, 0x4510, 0x8912, 0x7C35, 0xAD1F,
    0x0A6E, 0x41F3, 0x8A6F, 0x7CFF, 0xAA96, 0x0DAD, 0x3F39, 0x8BAC, 0x7D99, 0xA87D,
    0x1067, 0x3CE9, 0x8CC2, 0x7E0C, 0xA6CC, 0x129E, 0x3B07, 0x8DA8, 0x7E5E, 0xA57F,
    0x1452, 0x3995, 0x8E58, 0x7E96, 0xA492, 0x1585, 0x3897, 0x8ED0, 0x7EB7, 0xA402,
    0x1635, 0x380D, 0x8F0C, 0x7EC5, 0xA3CE, 0x1665, 0x37F9, 0x8F0A, 0x7EC1, 0xA3F5,
    0x1614, 0x385A, 0x8ECB, 0x7EAA, 0xA478, 0x1542, 0x3931, 0x8E50, 0x7E7F, 0xA557,
    0x13EF, 0x3A7B, 0x8D9C, 0x7E3C, 0xA696, 0x1219, 0x3C37, 0x8CB3, 0x7DDC, 0xA838,
    0x0FC1, 0x3E62, 0x8B9B, 0x7D59, 0xAA42, 0x0CE5, 0x40F7, 0x8A5C, 0x7CAA, 0xACBA,
    0x0985, 0x43F3, 0x88FD, 0x7BC6, 0xAFA6, 0x05A0, 0x474F, 0x878A, 0x7AA3, 0xB30C,
    0x0137, 0x4B03, 0x860F, 0x7934, 0xB6F4, 0xFC4C, 0x4F06, 0x8499, 0x776B, 0xBB65,
    0xF6DF, 0x534E, 0x8339, 0x753C, 0xC065, 0xF0F3, 0x57CD, 0x81FF, 0x7296, 0xC5FC,
    0xEA90, 0x5C75, 0x80FF, 0x6F6A, 0xCC30, 0xE3BA, 0x6134, 0x804E, 0x6BA8, 0xD304,
    0xDC7C, 0x65F6, 0x8003, 0x673F, 0xDA7B, 0xD4E2, 0x6AA5, 0x8034, 0x6221, 0xE296,
    0xCCFA, 0x6F29, 0x80FB, 0x5C3F, 0xEB53, 0xC4D8, 0x7365, 0x8272, 0x558C, 0xF4AB,
    0xBC92, 0x773A, 0x84B3, 0x4DFD, 0xFE97, 0xB441, 0x7A8A, 0x87D6, 0x458B, 0x0906,
    0xAC05, 0x7D30, 0x8BF5, 0x3C31, 0x13E8, 0xA3FF, 0x7F08, 0x9127, 0x31F0, 0x1F23,
    0x9C57, 0x7FEE, 0x9780, 0x26CD, 0x2A9B, 0x9537, 0x7FBC, 0x9F11, 0x1AD5, 0x3629,
    0x8ECD, 0x7E4D, 0xA7E5, 0x0E1B, 0x41A4, 0x894A, 0x7B7D, 0xB201, 0x00B9, 0x4CDB,
    0x84E1, 0x772E, 0xBD65, 0xF2D4, 0x5796, 0x81C6, 0x7144, 0xCA06, 0xE496, 0x6199,
    0x802E, 0x69AB, 0xD7D1, 0xD635, 0x6AA3, 0x8049, 0x6055, 0xE6A5, 0xC7F1, 0x726F,
    0x8247, 0x5540, 0xF65A, 0xBA0F, 0x78B6, 0x864E, 0x4874, 0x06B6, 0xACE0, 0x7D33,
    0x8C7D, 0x3A09, 0x1778, 0xA0BA, 0x7FA0, 0x94EA, 0x2A23, 0x284E, 0x95F7, 0x7FC0,
    0x9F9B, 0x18F8, 0x38DA, 0x8CF5, 0x7D5C, 0xAC86, 0x06CF, 0x48B6, 0x8612, 0x784A,
    0xBB90, 0xF400, 0x5771, 0x81A6, 0x706F, 0xCC88, 0xE0F4, 0x6495, 0x8002, 0x65C2,
    0xDF27, 0xCE25, 0x6FA7, 0x816D, 0x5852, 0xF311, 0xBC19, 0x7831, 0x861A, 0x4846,
    0x07CF, 0xAB62, 0x7DC3, 0x8E26, 0x35E2, 0x1CD9, 0x9C96, 0x7FF8, 0x9995, 0x2187,
    0x3190, 0x9050, 0x7E81, 0xA84C, 0x0BB4, 0x4547, 0x8721, 0x7925, 0xBA0C, 0xF505,
    0x5743, 0x8190, 0x6FCD, 0xCE72, 0xDE2F, 0x66CA, 0x800D, 0x6286, 0xE4F5, 0xC800,
    0x7323, 0x82ED, 0x5188, 0xFCE7, 0xB354, 0x7BA2, 0x8A5D, 0x3D38, 0x1575, 0xA10E,
    0x7FB4, 0x965F, 0x262D, 0x2DB2, 0x920F, 0x7EE7, 0xA6C0, 0x0D2A, 0x449C, 0x872B,
    0x78F7, 0xBB15, 0xF31F, 0x5923, 0x8119, 0x6DD6, 0xD2BA, 0xD91F, 0x6A3A, 0x8067,
    0x5DB3, 0xECCF, 0xC059, 0x76E7, 0x856E, 0x4906, 0x0840, 0xAA0C, 0x7E4F, 0x9045,
    0x3088, 0x23CE, 0x976F, 0x7FC7, 0xA0B6, 0x153C, 0x3E19, 0x89A9, 0x7AEA, 0xB638,
    0xF863, 0x55B2, 0x81B4, 0x6F9F, 0xCFF0, 0xDB6F, 0x6930, 0x804F, 0x5E2E, 0xECAE,
    0xBFF7, 0x7747, 0x85E6, 0x473D, 0x0AF9, 0xA7A0, 0x7EE0, 0x9282, 0x2BD9, 0x2924,
    0x9400, 0x7F36, 0xA5BF, 0x0D6C, 0x455A, 0x8684, 0x77E4, 0xBEC3, 0xEDB2, 0x5DC2,
    0x8052, 0x6901, 0xDC41, 0xCE9F, 0x709B, 0x822B, 0x5326, 0xFC82, 0xB245, 0x7C63,
    0x8C52, 0x3774, 0x1D7D, 0x9AB2, 0x7FF6, 0x9E78, 0x1790, 0x3CF1, 0x89C4, 0x7AB2,
    0xB7B5, 0xF58B, 0x588C, 0x80FF, 0x6C93, 0xD685, 0xD3C8, 0x6E1B, 0x8168, 0x563F,
    0xF8D9, 0xB4D4, 0x7BB7, 0x8B60, 0x390E, 0x1C36, 0x9B36, 0x7FF8, 0x9E89, 0x1700,
    0x3DDB, 0x8931, 0x7A1E, 0xB9BE, 0xF2A2, 0x5AF7, 0x8093, 0x6A38, 0xDB17, 0xCEDE,
    0x70ED, 0x8279, 0x5131, 0x0000, 0xAECB, 0x7D8B, 0x8F2A, 0x30D4, 0x2566, 0x955F,
    0x7F54, 0xA5F6, 0x0BB8, 0x47F5, 0x852A, 0x75AE, 0xC532, 0xE512, 0x6462, 0x8008,
    0x610A, 0xEA4A, 0xC06F, 0x77C1, 0x86E7, 0x42F1, 0x11EA, 0xA16D, 0x7FD8, 0x9992,
    0x1DF6, 0x3849, 0x8B53, 0x7B6B, 0xB6A1, 0xF58B, 0x597D, 0x80B3, 0x6A72, 0xDB81,
    0xCDB3, 0x71E7, 0x8315, 0x4E3A, 0x049F, 0xAAA6, 0x7E9E, 0x92B5, 0x295D, 0x2DBC,
    0x9057, 0x7DD5, 0xAE5B, 0xFF92, 0x5253, 0x8200, 0x6F24, 0xD362, 0xD556, 0x6E1E,
    0x81AB, 0x53B8, 0xFDE7, 0xAF7D, 0x7D9A, 0x8FE3, 0x2E4C, 0x2924, 0x929E, 0x7E86,
    0xAB7B, 0x02FA, 0x4FF9, 0x827F, 0x7045, 0xD192, 0xD6D1, 0x6D80, 0x818A, 0x5412,
    0xFDCE, 0xAF47, 0x7DB9, 0x9061, 0x2D04, 0x2ACA, 0x9189, 0x7E20, 0xADA4, 0xFFC4,
    0x52BD, 0x81C8, 0x6E21, 0xD5F8, 0xD211, 0x7036, 0x8290, 0x4F55, 0x0454, 0xAA0C,
    0x7EE2, 0x944F, 0x2571, 0x3294, 0x8D62, 0x7C42, 0xB51C, 0xF5EF, 0x5A42, 0x8075,
    0x6828, 0xE0CE, 0xC75E, 0x7581, 0x859E, 0x44EB, 0x116E, 0xA086, 0x7FF6, 0x9CAB,
    0x173D, 0x3FFA, 0x8763, 0x778F, 0xC2B9, 0xE5A5, 0x6561, 0x802B, 0x5CFF, 0xF275,
    0xB795, 0x7BA2, 0x8C86, 0x33D4, 0x24BD, 0x9457, 0x7ECC, 0xAB19, 0x021D, 0x51B4,
    0x81D7, 0x6DCC, 0xD789, 0xCF98, 0x71ED, 0x8392, 0x4ACF, 0x0AFB, 0xA485, 0x7FBB,
    0x99D6, 0x1B1E, 0x3D14, 0x8850, 0x7846, 0xC17C, 0xE669, 0x654A, 0x8032, 0x5C39,
    0xF433, 0xB5A0, 0x7C61, 0x8E26, 0x2FE1, 0x296D, 0x9170, 0x7DCD, 0xB053, 0xFAA9,
    0x57C4, 0x80A9, 0x68B2, 0xE122, 0xC5EF, 0x769C, 0x86E4, 0x404D, 0x1804, 0x9B6B,
    0x7FD8, 0xA39A, 0x0B9B, 0x4AE6, 0x835E, 0x7123, 0xD1FA, 0xD444, 0x6FFF, 0x82DC,
    0x4CAC, 0x0994, 0xA4E0, 0x7FC1, 0x9A9F, 0x18F8, 0x3FC7, 0x86F4, 0x7684, 0xC69A,
    0xDFE5, 0x69C0, 0x80EF, 0x5578, 0xFE79, 0xACD0, 0x7EAD, 0x94A9, 0x22BE, 0x371D,
    0x8A61, 0x79B2, 0xBEB7, 0xE868, 0x64C2, 0x8036, 0x5B33, 0xF6D3, 0xB292, 0x7D75,
    0x9114, 0x290A, 0x3156, 0x8CE7, 0x7B5E, 0xBA04, 0xED99, 0x6199, 0x8008, 0x5E48,
    0xF2A3, 0xB5BD, 0x7CAE, 0x8F6B, 0x2C00, 0x2EAC, 0x8E11, 0x7BF9, 0xB84A, 0xEF64,
    0x6098, 0x8003, 0x5EF6, 0xF1E5, 0xB622, 0x7CA1, 0x8F71, 0x2BB4, 0x2F37, 0x8DAF,
    0x7BB0, 0xB970, 0xEDC3, 0x61D6, 0x800D, 0x5D4E, 0xF497, 0xB3B9, 0x7D54, 0x9127,
    0x2823, 0x32F2, 0x8BD0, 0x7A6F, 0xBD85, 0xE8BA, 0x6536, 0x8053, 0x592B, 0xFABE,
    0xAEA8, 0x7E84, 0x94CC, 0x2136, 0x39BB, 0x88C6, 0x77DB, 0xC4BE, 0xE05E, 0x6A5E,
    0x8149, 0x5239, 0x045C, 0xA745, 0x7FA8, 0x9AD7, 0x16CA, 0x4348, 0x8528, 0x7359,
    0xCF64, 0xD4E2, 0x70B3, 0x83AA, 0x4802, 0x1163, 0x9E27, 0x7FEC, 0xA3EB, 0x08C3,
    0x4F17, 0x81DA, 0x6C1B, 0xDDC5, 0xC6AA, 0x774A, 0x886C, 0x3A04, 0x2194, 0x9432,
    0x7E37, 0xB0C4, 0xF72E, 0x5C52, 0x800F, 0x612D, 0xF00D, 0xB66E, 0x7CE2, 0x90B7,
    0x27D0, 0x3462, 0x8AAB, 0x7934, 0xC210, 0xE263, 0x69BE, 0x8144, 0x519B, 0x0620,
    0xA553, 0x7FDF, 0x9DC1, 0x1140, 0x48C8, 0x8341, 0x6F6B, 0xD844, 0xCB3A, 0x75A4,
    0x872A, 0x3CA5, 0x1F61, 0x950E, 0x7E5C, 0xB09E, 0xF6AC, 0x5D26, 0x8004, 0x5F77,
    0xF352, 0xB334, 0x7DD3, 0x9378, 0x2200, 0x3A7B, 0x87E3, 0x7656, 0xC9F4, 0xD931,
    0x6F2B, 0x8341, 0x4852, 0x1264, 0x9C9E, 0x7FBD, 0xA799, 0x0231, 0x5532, 0x809B,
    0x65FA, 0xE99B, 0xBAE9, 0x7BE1, 0x8F32, 0x29BB, 0x3390, 0x8A93, 0x78C3, 0xC43E,
    0xDEE5, 0x6C55, 0x8237, 0x4C1D, 0x0E33, 0x9F0E, 0x7FE8, 0xA57F, 0x04B3, 0x53A2,
    0x80C7, 0x66B5, 0xE8D3, 0xBB37, 0x7BE5, 0x8F6E, 0x28DA, 0x34CD, 0x89E1, 0x7802,
    0xC698, 0xDBF0, 0x6E28, 0x8301, 0x4890, 0x12F3, 0x9BBA, 0x7F93, 0xA9E5, 0xFE32,
    0x58C3, 0x802E, 0x61DE, 0xF0F6, 0xB413, 0x7DDD, 0x9444, 0x1F50, 0x3E12, 0x8624,
    0x73A5, 0xD13E, 0xD083, 0x73FF, 0x866C, 0x3D2A, 0x2079, 0x9384, 0x7D8D, 0xB5A4,
    0xEEB8, 0x638A, 0x8060, 0x5637, 0x022B, 0xA69D, 0x7FE3, 0x9F5E, 0x0CA6, 0x4E41,
    0x818F, 0x698E, 0xE506, 0xBDA3, 0x7B6C, 0x8F0C, 0x28A7, 0x35EC, 0x8907, 0x76D4,
    0xCA79, 0xD6DC, 0x7141, 0x84CB, 0x417F, 0x1C34, 0x9595, 0x7E23, 0xB387, 0xF0B9,
    0x62A2, 0x8050, 0x5665, 0x0285, 0xA5F1, 0x7FF0, 0xA0C6, 0x09F0, 0x50DA, 0x8103,
    0x66F2, 0xEA06, 0xB8D8, 0x7CF0, 0x9271, 0x2181, 0x3D1F, 0x861C, 0x7316, 0xD38F,
    0xCD21, 0x75F7, 0x8872, 0x36B9, 0x2888, 0x8EBB, 0x7B03, 0xBFB1, 0xE1CC, 0x6BEA,
    0x827D, 0x492A, 0x13FC, 0x99FF, 0x7F1E, 0xAEBA, 0xF60A, 0x5FA7, 0x801B, 0x58A3,
    0x0034, 0xA70D, 0x7FEA, 0xA0BF, 0x0939, 0x51FC, 0x80C1, 0x6525, 0xEDB8, 0xB526,
    0x7DF9, 0x95AB, 0x1AEE, 0x43A0, 0x83D7, 0x6ED9, 0xDCDE, 0xC3A1, 0x79E3, 0x8D47,
    0x2AE1, 0x3528, 0x88C8, 0x7600, 0xCDDA, 0xD1F6, 0x743B, 0x8748, 0x38F0, 0x2711,
    0x8F06, 0x7AEE, 0xC0C0, 0xDFB8, 0x6D87, 0x8354, 0x4517, 0x19B7, 0x9611, 0x7DFF,
    0xB589, 0xEC99, 0x6641, 0x810E, 0x4F65, 0x0D5E, 0x9D78, 0x7F91, 0xAC1C, 0xF860,
    0x5ED0, 0x8019, 0x57FA, 0x0233, 0xA4DE, 0x7FFE, 0xA454, 0x02E7, 0x578A, 0x801E,
    0x5EFF, 0xF853, 0xABF2, 0x7F9C, 0x9E07, 0x0C1D, 0x50B6, 0x80CC, 0x64A0, 0xEFCA,
    0xB277, 0x7EB4, 0x9907, 0x13F8, 0x4A8C, 0x81DD, 0x690B, 0xE89D, 0xB83B, 0x7D89,
    0x9526, 0x1A78, 0x4537, 0x8315, 0x6C6B, 0xE2C9, 0xBD19, 0x7C51, 0x923D, 0x1FA1,
    0x40D7, 0x8442, 0x6EE6, 0xDE48, 0xC0F6, 0x7B38, 0x9029, 0x237C, 0x3D82, 0x853F,
    0x709B, 0xDB13, 0xC3BE, 0x7A5E, 0x8ECD, 0x260D, 0x3B4A, 0x85EF, 0x71A1, 0xD923,
    0xC565, 0x79DC, 0x8E18, 0x275D, 0x3A36, 0x8641, 0x7209, 0xD873, 0xC5E4, 0x79BD,
    0x8DFD, 0x276D, 0x3A4D, 0x862C, 0x71D7, 0xD903, 0xC538, 0x7A04, 0x8E7C, 0x263D,
    0x3B8D, 0x85B3, 0x710A, 0xDAD3, 0xC365, 0x7AAC, 0x8F9B, 0x23CC, 0x3DF1, 0x84E2,
    0x6F94, 0xDDE7, 0xC073, 0x7BA2, 0x916C, 0x2013, 0x416E, 0x83CD, 0x6D62, 0xE247,
    0xBC6E, 0x7CCC, 0x9407, 0x1B0B, 0x45F5, 0x8297, 0x6A56, 0xE7F8, 0xB76C, 0x7E05,
    0x978D, 0x14AE, 0x4B6C, 0x8168, 0x664D, 0xEF03, 0xB188, 0x7F1C, 0x9C23, 0x0CF6,
    0x51B3, 0x8077, 0x611D, 0xF769, 0xAAEA, 0x7FD7, 0xA1F7, 0x03E2, 0x589B, 0x8003,
    0x5A9A, 0x0127, 0xA3C5, 0x7FF0, 0xA935, 0xF97C, 0x5FED, 0x8058, 0x5296, 0x0C32,
    0x9C5A, 0x7F18, 0xB20A, 0xEDD4, 0x675D, 0x81C9, 0x48E6, 0x186E, 0x94FA, 0x7CF8,
    0xBC9D, 0xE10D, 0x6E95, 0x84B0, 0x3D68, 0x25B1, 0x8E06, 0x7934, 0xC90D, 0xD35E,
    0x7528, 0x896A, 0x3004, 0x33BA, 0x87F1, 0x736C, 0xD765, 0xC514, 0x7A9D, 0x9054,
    0x20B9, 0x422C, 0x833E, 0x6B4A, 0xE79F, 0xB697, 0x7E6A, 0x99C3, 0x0F9B, 0x5092,
    0x807C, 0x607D, 0xF991, 0xA86D, 0x7FFC, 0xA5FB, 0xFCE6, 0x5E56, 0x8041, 0x52CE,
    0x0CF2, 0x9B3C, 0x7EBA, 0xB528, 0xE8F7, 0x6AC6, 0x8324, 0x4223, 0x214B, 0x8FC1,
    0x7A14, 0xC74D, 0xD45D, 0x7515, 0x89AE, 0x2E8D, 0x35F6, 0x86D4, 0x718A, 0xDC42,
    0xBFD7, 0x7C67, 0x944F, 0x1854, 0x4A1C, 0x8156, 0x64BF, 0xF39E, 0xAC54, 0x7FD8,
    0xA34F, 0x0000, 0x5CB5, 0x8029, 0x5388, 0x0CB5, 0x9AF1, 0x7E8E, 0xB6B6, 0xE664,
    0x6C94, 0x8418, 0x3E02, 0x268F, 0x8CE8, 0x77D2, 0xCE3F, 0xCC9D, 0x7873, 0x8DC0,
    0x24A0, 0x3FE9, 0x8384, 0x6B28, 0xE942, 0xB412, 0x7F0B, 0x9D76, 0x083F, 0x573B,
    0x8002, 0x586B, 0x06AE, 0x9E67, 0x7F33, 0xB328, 0xEA28, 0x6ACE, 0x8370, 0x3FE7,
    0x2502, 0x8D61, 0x7801, 0xCE46, 0xCC14, 0x78D4, 0x8E85, 0x227A, 0x4251, 0x82C8,
    0x68FA, 0xEDA6, 0xB01B, 0x7F9A, 0xA178, 0x0198, 0x5C5E, 0x8032, 0x5239, 0x0F83,
    0x9894, 0x7DB4, 0xBBD3, 0xDF57, 0x70C3, 0x86CC, 0x3493, 0x3180, 0x87E7, 0x7241,
    0xDC59, 0xBE55, 0x7D29, 0x9721, 0x11B3, 0x50C6, 0x8049, 0x5D20, 0x00F1, 0xA194,
    0x7F92, 0xB0D8, 0xEC1C, 0x6A3A, 0x836A, 0x3F2C, 0x26B6, 0x8C32, 0x76AE, 0xD28C,
    0xC70F, 0x7AD0, 0x9225, 0x1A59, 0x4A18, 0x8110, 0x622F, 0xF9B9, 0xA653, 0x7FEF,
    0xAC2C, 0xF1BB, 0x6731, 0x8262, 0x430D, 0x22C4, 0x8DD5, 0x77E4, 0xCFCD, 0xC95E,
    0x7A2F, 0x913D, 0x1BB6, 0x4945, 0x8125, 0x6255, 0xF9E1, 0xA5F0, 0x7FE6, 0xAD2D,
    0xF008, 0x686B, 0x82E3, 0x4095, 0x25E6, 0x8C3A, 0x766A, 0xD3EF, 0xC50C, 0x7BA2,
    0x9427, 0x15D7, 0x4E68, 0x806C, 0x5D9A, 0x016A, 0xA07A, 0x7F50, 0xB400, 0xE70E,
    0x6D9D, 0x8557, 0x3787, 0x2FED, 0x87F4, 0x719D, 0xDF33, 0xBA7F, 0x7E4A, 0x9BAF,
    0x0892, 0x58CE, 0x8010, 0x531B, 0x104B, 0x96FE, 0x7CBE, 0xC183, 0xD725, 0x7559,
    0x8B5D, 0x2727, 0x401E, 0x82D4, 0x67C2, 0xF20E, 0xAAED, 0x7FFE, 0xA98B, 0xF3D9,
    0x66C1, 0x8283, 0x414D, 0x260F, 0x8BBB, 0x7593, 0xD6EE, 0xC15E, 0x7CDF, 0x979B,
    0x0EBB, 0x54B6, 0x8003, 0x565C, 0x0C96, 0x98CE, 0x7D47, 0xBFDF, 0xD85B, 0x7514,
    0x8B58, 0x269D, 0x4123, 0x8277, 0x6654, 0xF510, 0xA83F, 0x7FF4, 0xAD30, 0xEE69,
    0x6A44, 0x8401, 0x3AE8, 0x2D8D, 0x886C, 0x71A8, 0xE04B, 0xB888, 0x7ED3, 0x9EBE,
    0x028A, 0x5DE4, 0x8099, 0x4B7B, 0x1B14, 0x9084, 0x7910, 0xCEA8, 0xC878, 0x7B1A,
    0x9412, 0x142B, 0x512B, 0x801A, 0x5888, 0x0A75, 0x9994, 0x7D5F, 0xC032, 0xD733,
    0x75E5, 0x8C91, 0x230A, 0x4507, 0x8186, 0x6275, 0xFC23, 0xA2A6, 0x7F6D, 0xB4BD,
    0xE424, 0x7022, 0x878F, 0x2F1F, 0x3A27, 0x83FF, 0x69BB, 0xF04F, 0xAAFD, 0x7FFE,
    0xABFC, 0xEEEE, 0x6A91, 0x8469, 0x3887, 0x3105, 0x86CC, 0x6ED9, 0xE70B, 0xB20D,
    0x7FBA, 0xA59C, 0xF760, 0x65C5, 0x8290, 0x3F6E, 0x29ED, 0x895D, 0x723E, 0xE04C,
    0xB776, 0x7F25, 0xA14D, 0xFD62, 0x6227, 0x8193, 0x4403, 0x250F, 0x8B48, 0x7445,
    0xDC04, 0xBAF9, 0x7EA0, 0x9ECF, 0x00EC, 0x5FFE, 0x8121, 0x466C, 0x2286, 0x8C4B,
    0x752B, 0xDA23, 0xBC72, 0x7E65, 0x9DFA, 0x01FC, 0x5F6F, 0x810D, 0x46BF, 0x225D,
    0x8C45, 0x750E, 0xDA9F, 0xBBD2, 0x7E8B, 0x9EBE, 0x0094, 0x6084, 0x814D, 0x4500,
    0x2495, 0x8B36, 0x73E9, 0xDD7C, 0xB921, 0x7F03, 0xA129, 0xFCB2, 0x632A, 0x81FD,
    0x411E, 0x2924, 0x8940, 0x7198, 0xE2C6, 0xB477, 0x7F9B, 0xA563, 0xF659, 0x6732,
    0x835C, 0x3AF8, 0x2FF2, 0x86AA, 0x6DD6, 0xEA8C, 0xAE0A, 0x7FFC, 0xABAA, 0xED92,
    0x6C4A, 0x85CC, 0x325F, 0x38D2, 0x83DD, 0x6844, 0xF4DE, 0xA62A, 0x7FA8, 0xB44F,
    0xE277, 0x71FE, 0x89CE, 0x2727, 0x437C, 0x816C, 0x606E, 0x01BB, 0x9D50, 0x7E00,
    0xBFA5, 0xD540, 0x77AB, 0x8FFC, 0x192B, 0x4F7E, 0x8013, 0x55D4, 0x110A, 0x9425,
    0x7A45, 0xCDF9, 0xC650, 0x7C82, 0x98FF, 0x0865, 0x5C2F, 0x80B0, 0x47FF, 0x227E,
    0x8B87, 0x73A3, 0xDF78, 0xB644, 0x7F86, 0xA57F, 0xF503, 0x68AB, 0x8442, 0x3693,
    0x3588, 0x848B, 0x6942, 0xF41C, 0xA606, 0x7F91, 0xB607, 0xDF7A, 0x73C6, 0x8BD0,
    0x216F, 0x4945, 0x807E, 0x5A62, 0x0B87, 0x96D0, 0x7B69, 0xCAEB, 0xC8A6, 0x7C10,
    0x9855, 0x08C9, 0x5C6C, 0x80CE, 0x467D, 0x24F1, 0x8A33, 0x71DA, 0xE418, 0xB1D8,
    0x7FE8, 0xAA8E, 0xED5B, 0x6D4C, 0x86EB, 0x2D74, 0x3F03, 0x8208, 0x61E6, 0x00F2,
    0x9CE0, 0x7D9A, 0xC2CF, 0xD07A, 0x79D7, 0x9419, 0x0FC5, 0x57CE, 0x8046, 0x4AFF,
    0x2028, 0x8C04, 0x739A, 0xE0C0, 0xB42E, 0x7FCB, 0xA926, 0xEEBC, 0x6CD6, 0x86CC,
    0x2D52, 0x3F94, 0x81D5, 0x60D0, 0x0322, 0x9B31, 0x7CF2, 0xC61A, 0xCC93, 0x7B36,
    0x9703, 0x0A09, 0x5C44, 0x80E5, 0x44F7, 0x27A7, 0x88BF, 0x6F8A, 0xE9E3, 0xAC79,
    0x7FF4, 0xB171, 0xE388, 0x729F, 0x8B5A, 0x2106, 0x4ADE, 0x803D, 0x56C2, 0x120B,
    0x926A, 0x7883, 0xD543, 0xBD7E, 0x7ECA, 0xA256, 0xF782, 0x6868, 0x84AC, 0x3345,
    0x3AA2, 0x82BB, 0x6366, 0xFFE7, 0x9CB6, 0x7D4B, 0xC55B, 0xCC9D, 0x7B6A, 0x97E9,
    0x07B1, 0x5E6B, 0x816B, 0x40EC, 0x2CE1, 0x8697, 0x6BDE, 0xF1BD, 0xA60E, 0x7F5D,
    0xB9D7, 0xD8CF, 0x776C, 0x9127, 0x13CE, 0x55FC, 0x8039, 0x4A6B, 0x2262, 0x8A6C,
    0x7123, 0xE7AC, 0xAD5C, 0x7FF5, 0xB23C, 0xE181, 0x73FF, 0x8D2A, 0x1BD7, 0x4FFA,
    0x8002, 0x5041, 0x1B8F, 0x8D40, 0x7404, 0xE1A4, 0xB1F2, 0x7FF8, 0xAE14, 0xE66A,
    0x71E9, 0x8B44, 0x1FE6, 0x4CE8, 0x8010, 0x52CE, 0x1898, 0x8E7D, 0x7507, 0xDF8A,
    0xB372, 0x7FEE, 0xAD14, 0xE76B, 0x7192, 0x8B15, 0x200E, 0x4D01, 0x800D, 0x5246,
    0x198E, 0x8DE9, 0x7464, 0xE152, 0xB1C0, 0x7FFC, 0xAF27, 0xE47E, 0x730B, 0x8C94,
    0x1C52, 0x5044, 0x8003, 0x4E9E, 0x1E6D, 0x8B9D, 0x71F8, 0xE708, 0xACFD, 0x7FE8,
    0xB476, 0xDDB5, 0x760C, 0x900C, 0x149D, 0x5670, 0x805B, 0x4790, 0x2716, 0x880F,
    0x6D4C, 0xF0C4, 0xA589, 0x7F18, 0xBD5E, 0xD33F, 0x79F2, 0x961B, 0x08D5, 0x5EFF,
    0x81E0, 0x3CAE, 0x333F, 0x8413, 0x65A1, 0xFE98, 0x9C18, 0x7C95, 0xCA5A, 0xC585,
    0x7DB6, 0x9FA0, 0xF8FA, 0x690A, 0x85B5, 0x2D7A, 0x4258, 0x80E4, 0x5A03, 0x106C,
    0x91C9, 0x7713, 0xDBE0, 0xB54F, 0x7FE7, 0xAD98, 0xE54A, 0x7337, 0x8D47, 0x1994,
    0x5359, 0x8029, 0x4973, 0x25C7, 0x8838, 0x6D0D, 0xF226, 0xA3EA, 0x7EAC, 0xC0F3,
    0xCE87, 0x7BA2, 0x9A25, 0x0101, 0x64A3, 0x83E2, 0x3327, 0x3D94, 0x818D, 0x5CF8,
    0x0CD9, 0x9352, 0x77E8, 0xDA41, 0xB62C, 0x7FE2, 0xADC1, 0xE478, 0x73D9, 0x8E3A,
    0x16E3, 0x55E2, 0x806B, 0x4599, 0x2ACA, 0x8643, 0x697B, 0xF94E, 0x9EA9, 0x7D2F,
    0xC901, 0xC5B7, 0x7DE8, 0xA12A, 0xF567, 0x6BBC, 0x87A7, 0x267F, 0x4996, 0x801C,
    0x51B8, 0x1CAE, 0x8B74, 0x70C5, 0xEBBA, 0xA7D1, 0x7F3D, 0xBDE6, 0xD0E4, 0x7B38,
    0x99CA, 0x009D, 0x657B, 0x847A, 0x3014, 0x4155, 0x80D7, 0x588A, 0x140D, 0x8F31,
    0x745F, 0xE41E, 0xAD53, 0x7FD0, 0xB83F, 0xD6DC, 0x7974, 0x967B, 0x05ED, 0x6261,
    0x8359, 0x3402, 0x3DED, 0x814C, 0x5AD8, 0x1133, 0x906A, 0x7544, 0xE253, 0xAE78,
    0x7FDE, 0xB797, 0xD749, 0x796C, 0x969F, 0x0555, 0x62FA, 0x83A6, 0x3282, 0x3FA8,
    0x80FD, 0x58EF, 0x1432, 0x8ECC, 0x73B9, 0xE64D, 0xAB1C, 0x7F91, 0xBBDD, 0xD225,
    0x7B23, 0x9A3D, 0xFED4, 0x672E, 0x858D, 0x2B7D, 0x4662, 0x803B, 0x5290, 0x1CF8,
    0x8AC4, 0x6F48, 0xF026, 0xA3AA, 0x7E40, 0xC571, 0xC7B8, 0x7DD0, 0xA200, 0xF270,
    0x6E35, 0x8A00, 0x1E9D, 0x517B, 0x802C, 0x46F9, 0x2B35, 0x8581, 0x66CD, 0x0000,
    0x9930, 0x7A79, 0xD4F8, 0xB8C1, 0x7FDA, 0xAF16, 0xE06A, 0x7680, 0x92A5, 0x0B87,
    0x5FAA, 0x82C3, 0x3528, 0x3E18, 0x8113, 0x58A3, 0x15B2, 0x8D98, 0x7214, 0xEB0E,
    0xA6C2, 0x7ECC, 0xC2E5, 0xC9A2, 0x7D8E, 0xA196, 0xF24A, 0x6EAA, 0x8AA8, 0x1C42,
    0x53E8, 0x806F, 0x4306, 0x304B, 0x83DA, 0x6281, 0x07B6, 0x945F, 0x7779, 0xDE7F,
    0xB017, 0x7FE1, 0xB8F1, 0xD3FD, 0x7B02, 0x9AE1, 0xFC43, 0x698B, 0x874B, 0x24BD,
    0x4D6B, 0x8008, 0x4954, 0x299D, 0x85A8, 0x666A, 0x01CF, 0x9772, 0x7934, 0xDA01,
    0xB379, 0x7FFC, 0xB618, 0xD6DC, 0x7A41, 0x9988, 0xFE14, 0x68BD, 0x86F7, 0x254D,
    0x4D46, 0x8009, 0x48CE, 0x2A9A, 0x853D, 0x6549, 0x0415, 0x95EB, 0x782D, 0xDD5C,
    0xB05F, 0x7FDB, 0xBA01, 0xD207, 0x7BC8, 0x9D36, 0xF7B8, 0x6C7C, 0x897E, 0x1DFA,
    0x537F, 0x807E, 0x4163, 0x3330, 0x82DC, 0x5ED6, 0x0E82, 0x903B, 0x73D5, 0xE8BC,
    0xA746, 0x7EAB, 0xC527, 0xC5DF, 0x7E8F, 0xA6C8, 0xE94A, 0x73AA, 0x9022, 0x0E75,
    0x5F10, 0x8301, 0x323D, 0x429F, 0x8057, 0x51AD, 0x20CE, 0x8838, 0x6A41, 0xFC78,
    0x99D6, 0x7A10, 0xD898, 0xB3A0, 0x7FF7, 0xB80F, 0xD365, 0x7BA2, 0x9D66, 0xF68C,
    0x6D90, 0x8AA2, 0x1A42, 0x5700, 0x8119, 0x3BC2, 0x39D2, 0x8165, 0x587F, 0x185C,
    0x8B5A, 0x6E5D, 0xF53A, 0x9E10, 0x7BD1, 0xD313, 0xB800, 0x7FFA, 0xB46F, 0xD721,
    0x7AAF, 0x9B80, 0xF917, 0x6C79, 0x8A00, 0x1B5F, 0x5682, 0x8112, 0x3B84, 0x3A7B,
    0x8139, 0x5746, 0x1A78, 0x8A4B, 0x6CC4, 0xF8C8, 0x9B84, 0x7A99, 0xD7C5, 0xB390,
    0x7FF1, 0xB9AF, 0xD0B1, 0x7C92, 0xA083, 0xF0DB, 0x70DB, 0x8DDE, 0x11D9, 0x5DB5,
    0x82E0, 0x317C, 0x4483, 0x8021, 0x4DBA, 0x2701, 0x85AC, 0x64CD, 0x0728, 0x9303,
    0x7553, 0xE708, 0xA72B, 0x7E5D, 0xC8A7, 0xC0C5, 0x7F7A, 0xADE0, 0xDE23, 0x78BB,
    0x984B, 0xFD69, 0x6AAC, 0x891F, 0x1CA8, 0x5647, 0x812A, 0x3A04, 0x3CDD, 0x80C4,
    0x53C8, 0x2005, 0x87D3, 0x6882, 0x017B, 0x95CC, 0x7718, 0xE30A, 0xA9C2, 0x7ECF,
    0xC66B, 0xC27A, 0x7F57, 0xAD32, 0xDE7C, 0x78CA, 0x98B5, 0xFC2C, 0x6BA4, 0x89FE,
    0x19E4, 0x58BB, 0x81BE, 0x3609, 0x412D, 0x8049, 0x4F23, 0x2651, 0x8592, 0x63EE,
    0x099F, 0x9133, 0x736A, 0xEC9B, 0xA274, 0x7CE4, 0xD0C2, 0xB859, 0x7FFE, 0xB776,
    0xD1B3, 0x7CB0, 0xA1EF, 0xED2E, 0x7342, 0x9127, 0x0967, 0x6448, 0x85DA, 0x24FF,
    0x5096, 0x8077, 0x3EA7, 0x3932, 0x8121, 0x5532, 0x1F48, 0x87B3, 0x67A4, 0x0419,
    0x93C1, 0x7539, 0xE8E8, 0xA4A3, 0x7D6D, 0xCEEE, 0xB97F, 0x7FFD, 0xB74D, 0xD154,
    0x7CE8, 0xA304, 0xEB07, 0x7470, 0x92E0, 0x0574, 0x670C, 0x877D, 0x1F78, 0x5567,
    0x813D, 0x37FE, 0x4055, 0x8046, 0x4E0A, 0x28C5, 0x8487, 0x60C3, 0x0FBA, 0x8DB8,
    0x6F7B, 0xF63C, 0x9B5F, 0x79B2, 0xDD4E, 0xACDD, 0x7F1B, 0xC5E6, 0xC16E, 0x7F9B,
    0xB0E0, 0xD83A, 0x7B48, 0x9EFB, 0xF057, 0x7267, 0x90CF, 0x08DA, 0x6564, 0x86CC,
    0x20DD, 0x54D1, 0x8138, 0x3785, 0x4159, 0x802B, 0x4C0E, 0x2BBC, 0x8395, 0x5DCB,
    0x14C7, 0x8B3D, 0x6C31, 0xFD4B, 0x96C9, 0x76D8, 0xE614, 0xA5BE, 0x7D7A, 0xCFE6,
    0xB78B, 0x7FF9, 0xBB73, 0xCB89, 0x7E58, 0xA95A, 0xE109, 0x78BE, 0x9A1D, 0xF754,
    0x6F6F, 0x8E26, 0x0DB5, 0x62CD, 0x85BC, 0x237E, 0x534D, 0x810C, 0x380B, 0x4177,
    0x8021, 0x4AC9, 0x2DE0, 0x82E9, 0x5B39, 0x1923, 0x893A, 0x68F2, 0x03DE, 0x92CE,
    0x73A3, 0xEEAE, 0x9F4D, 0x7B15, 0xDA23, 0xAE4C, 0x7F28, 0xC6C8, 0xBF55, 0x7FD9,
    0xB519, 0xD1E6, 0x7D39, 0xA57F, 0xE57C, 0x776F, 0x9852, 0xF98F, 0x6EB6, 0x8DD7,
    0x0D9C, 0x635B, 0x863C, 0x2126, 0x55B5, 0x819E, 0x33B9, 0x4629, 0x8002, 0x44EB,
    0x3521, 0x815E, 0x545F, 0x230D, 0x8594, 0x61C9, 0x105C, 0x8C77, 0x6CE9, 0xFD7E,
    0x95CD, 0x7594, 0xEADB, 0xA150, 0x7BAA, 0xD8D9, 0xAEB1, 0x7F1F, 0xC7D3, 0xBD9C,
    0x7FF4, 0xB81C, 0xCDB7, 0x7E38, 0xA9FB, 0xDEA5, 0x7A09, 0x9DAA, 0xF00C, 0x738E,
    0x9359, 0x0192, 0x6AF9, 0x8B2A, 0x12E2, 0x6083, 0x8532, 0x23AC, 0x546D, 0x817D,
    0x33A6, 0x46FB, 0x8008, 0x428F, 0x3875, 0x80C8, 0x502D, 0x2924, 0x83A7, 0x5C4F,
    0x1951, 0x8886, 0x66CF, 0x0942, 0x8F41, 0x6F8F, 0xF93E, 0x97AC, 0x767A, 0xE982,
    0xA196, 0x7B85, 0xDA4B, 0xACCC, 0x7EAC, 0xCBD0, 0xB916, 0x7FF5, 0xBE40, 0xC63E,
    0x7F6B, 0xB1C6, 0xD40A, 0x7D22, 0xA684, 0xE245, 0x7930, 0x9C97, 0xF0B7, 0x73B5,
    0x9415, 0xFF2D, 0x6CCF, 0x8D0C, 0x0D76, 0x64A5, 0x8786, 0x1B67, 0x5B5D, 0x8386,
    0x28D6, 0x511F, 0x8109, 0x359E, 0x4615, 0x8008, 0x41A0, 0x3A66, 0x8077, 0x4CBE,
    0x2E3E, 0x8245, 0x56E4, 0x21C2, 0x855F, 0x5FFD, 0x151A, 0x89B0, 0x67FC, 0x0869,
    0x8F1D, 0x6ED9, 0xFBD3, 0x958E, 0x748C, 0xEF75, 0x9CE6, 0x7915, 0xE36D, 0xA509,
    0x7C76, 0xD7D4, 0xADD9, 0x7EB3, 0xCCC2, 0xB73C, 0x7FD4, 0xC249, 0xC113, 0x7FE5,
    0xB87A, 0xCB44, 0x7EF1, 0xAF64, 0xD5B4, 0x7D07, 0xA711, 0xE04A, 0x7A36, 0x9F88,
    0xEAEF, 0x7691, 0x98D0, 0xF58B, 0x7228, 0x92EB, 0x0009, 0x6D0E, 0x8DD9, 0x0A5A,
    0x6756, 0x8999, 0x146B, 0x6113, 0x8629, 0x1E2D, 0x5A57, 0x8382, 0x2794, 0x5334,
    0x819F, 0x3094, 0x4BBD, 0x8078, 0x3924, 0x4403, 0x8004, 0x413D, 0x3C16, 0x803A,
    0x48D8, 0x3404, 0x810E, 0x4FF2, 0x2BDE, 0x8277, 0x5687, 0x23B0, 0x8469, 0x5C96,
    0x1B86, 0x86D9, 0x621F, 0x136D, 0x89BC, 0x6722, 0x0B6E, 0x8D05, 0x6BA1, 0x0393,
    0x90A9, 0x6F9F, 0xFBE4, 0x949E, 0x7321, 0xF467, 0x98D9, 0x7629, 0xED22, 0x9D4F,
    0x78BD, 0xE61C, 0xA1F6, 0x7AE2, 0xDF58, 0xA6C5, 0x7C9E, 0xD8D9, 0xABB3, 0x7DF7,
    0xD2A2, 0xB0B7, 0x7EF3, 0xCCB6, 0xB5C9, 0x7F99, 0xC714, 0xBAE2, 0x7FEF, 0xC1BE,
    0xBFFB, 0x7FFB, 0xBCB3, 0xC50E, 0x7FC4, 0xB7F3, 0xCA15, 0x7F51, 0xB37D, 0xCF0B,
    0x7EA7, 0xAF4F, 0xD3EB, 0x7DCE, 0xAB68, 0xD8B1, 0x7CCA, 0xA7C6, 0xDD59, 0x7BA2,
    0xA466, 0xE1E1, 0x7A5B, 0xA146, 0xE644, 0x78FB, 0x9E63, 0xEA82, 0x7787, 0x9BBB,
    0xEE96, 0x7603, 0x994A, 0xF281, 0x7474, 0x970E, 0xF640, 0x72DF, 0x9503, 0xF9D2,
    0x7147, 0x9328, 0xFD36, 0x6FB0, 0x9179, 0x006A, 0x6E1E, 0x8FF3, 0x0371, 0x6C93,
    0x8E93, 0x0647, 0x6B14, 0x8D57, 0x08EE, 0x69A2, 0x8C3D, 0x0B65, 0x6841, 0x8B41,
    0x0DAC, 0x66F2, 0x8A62, 0x0FC3, 0x65B8, 0x899D, 0x11AB, 0x6495, 0x88F1, 0x1363,
    0x6389, 0x885C, 0x14EB, 0x6297, 0x87DC, 0x1644, 0x61C1, 0x8770, 0x176F, 0x6106,
    0x8715, 0x186A, 0x6069, 0x86CC, 0x1937, 0x5FE9, 0x8694, 0x19D6, 0x5F88, 0x866B,
    0x1A46, 0x5F46, 0x8651, 0x1A88, 0x5F24, 0x8646, 0x1A9C, 0x5F21, 0x8649, 0x1A82,
    0x5F3D, 0x865B, 0x1A3A, 0x5F79, 0x867C, 0x19C3, 0x5FD4, 0x86AC, 0x191F, 0x604D,
    0x86EC, 0x184B, 0x60E4, 0x873D, 0x174A, 0x6199, 0x87A0, 0x1619, 0x626A, 0x8815,
    0x14BA, 0x6357, 0x889F, 0x132B, 0x645D, 0x893F, 0x116D, 0x657C, 0x89F6, 0x0F7F,
    0x66B2, 0x8AC7, 0x0D61, 0x67FD, 0x8BB3, 0x0B14, 0x695A, 0x8CBC, 0x0896, 0x6AC9,
    0x8DE6, 0x05E9, 0x6C46, 0x8F32, 0x030C, 0x6DCE, 0x90A4, 0x0000, 0x6F5F, 0x923D,
    0xFCC5, 0x70F5, 0x9400, 0xF95B, 0x728D, 0x95F1, 0xF5C3, 0x7424, 0x9812, 0xF1FE,
    0x75B4, 0x9A67, 0xEE0E, 0x773A, 0x9CF1, 0xE9F3, 0x78B2, 0x9FB4, 0xE5B1, 0x7A17,
    0xA2B3, 0xE148, 0x7B63, 0xA5F1, 0xDCBC, 0x7C91, 0xA970, 0xD810, 0x7D9D, 0xAD32,
    0xD346, 0x7E7F, 0xB139, 0xCE63, 0x7F33, 0xB589, 0xC96A, 0x7FB2, 0xBA21, 0xC461,
    0x7FF5, 0xBF04, 0xBF4D, 0x7FF7, 0xC432, 0xBA34, 0x7FB0, 0xC9AB, 0xB51B, 0x7F1B,
    0xCF70, 0xB00B, 0x7E31, 0xD580, 0xAB09, 0x7CEB, 0xDBD8, 0xA61F, 0x7B43, 0xE278,
    0xA155, 0x7934, 0xE95B, 0x9CB4, 0x76B6, 0xF07F, 0x9845, 0x73C6, 0xF7DF, 0x9413,
    0x705D, 0xFF74, 0x9028, 0x6C78, 0x0738, 0x8C8F, 0x6812, 0x0F25, 0x8953, 0x632A,
    0x1732, 0x867F, 0x5DBC, 0x1F54, 0x841F, 0x57C8, 0x2781, 0x823F, 0x514E, 0x2FAD,
    0x80E9, 0x4A4F, 0x37CC, 0x8029, 0x42CD, 0x3FCE, 0x800A, 0x3ACD, 0x47A6, 0x8095,
    0x3254, 0x4F43, 0x81D5, 0x2969, 0x5694, 0x83D1, 0x2016, 0x5D89, 0x8693, 0x1665,
    0x640F, 0x8A1E, 0x0C63, 0x6A14, 0x8E7A, 0x021E, 0x6F84, 0x93A8, 0xF7A7, 0x744E,
    0x99A9, 0xED0F, 0x785E, 0xA07E, 0xE26B, 0x7BA2, 0xA821, 0xD7D0, 0x7E09, 0xB08F,
    0xCD56, 0x7F82, 0xB9BF, 0xC317, 0x7FFE, 0xC3A5, 0xB92B, 0x7F70, 0xCE33, 0xAFAF,
    0x7DCB, 0xD959, 0xA6BF, 0x7B07, 0xE502, 0x9E77, 0x771C, 0xF117, 0x96F4, 0x7208,
    0xFD7E, 0x9053, 0x6BCA, 0x0A19, 0x8AB0, 0x6465, 0x16CB, 0x8624, 0x5BE0, 0x236F,
    0x82CA, 0x5248, 0x2FE2, 0x80B8, 0x47AC, 0x3BFD, 0x8002, 0x3C20, 0x4798, 0x80B8,
    0x2FBE, 0x528A, 0x82E8, 0x22A4, 0x5CA9, 0x869A, 0x14F3, 0x65CD, 0x8BD2, 0x06D3,
    0x6DCE, 0x928E, 0xF870, 0x7485, 0x9AC6, 0xE9F5, 0x79CE, 0xA46B, 0xDB97, 0x7D89,
    0xAF6B, 0xCD89, 0x7F98, 0xBBAA, 0xC002, 0x7FE5, 0xC905, 0xB33B, 0x7E5D, 0xD755,
    0xA76B, 0x7AF5, 0xE66A, 0x9CC9, 0x75AA, 0xF610, 0x938B, 0x6E7F, 0x060B, 0x8BE4,
    0x6582, 0x161D, 0x8602, 0x5AC8, 0x2602, 0x820E, 0x4E71, 0x3573, 0x8029, 0x40A4,
    0x4427, 0x806F, 0x3193, 0x51D6, 0x82F0, 0x2179, 0x5E37, 0x87B4, 0x1099, 0x6905,
    0x8EB6, 0xFF3E, 0x7200, 0x97E7, 0xEDB6, 0x78EB, 0xA32C, 0xDC5A, 0x7D93, 0xB05D,
    0xCB83, 0x7FCF, 0xBF43, 0xBB8C, 0x7F7F, 0xCFA0, 0xACD0, 0x7C91, 0xE126, 0x9FA9,
    0x7701, 0xF37F, 0x946C, 0x6ED9, 0x064A, 0x8B66, 0x6433, 0x1921, 0x84DB, 0x573A,
    0x2B97, 0x8104, 0x4828, 0x3D3C, 0x800D, 0x3749, 0x4DA0, 0x820F, 0x24F5, 0x5C56,
    0x8714, 0x1193, 0x68F6, 0x8F13, 0xFD96, 0x7321, 0x99ED, 0xE97A, 0x7A84, 0xA771,
    0xD5C0, 0x7EDA, 0xB758, 0xC2F0, 0x7FF2, 0xC947, 0xB18E, 0x7DAE, 0xDCD1, 0xA21D,
    0x7805, 0xF17B, 0x9515, 0x6F0B, 0x06B7, 0x8AE4, 0x62E7, 0x1BF2, 0x83E6, 0x53DE,
    0x3091, 0x8064, 0x424C, 0x43F5, 0x8090, 0x2EA5, 0x5583, 0x847F, 0x1971, 0x64A9,
    0x8C2C, 0x034B, 0x70E1, 0x9773, 0xECDF, 0x79B6, 0xA60F, 0xD6DC, 0x7ECC, 0xB7A0,
    0xC1F9, 0x7FE1, 0xCBA6, 0xAEEC, 0x7CD5, 0xE189, 0x9E60, 0x75A7, 0xF89B, 0x90F1,
    0x6A7B, 0x1019, 0x8728, 0x5B9C, 0x2739, 0x8171, 0x4977, 0x3D2C, 0x8018, 0x349B,
    0x5121, 0x8343, 0x1DB9, 0x6257, 0x8AEE, 0x0598, 0x701D, 0x96ED, 0xED15, 0x79DC,
    0xA6E7, 0xD517, 0x7F1F, 0xBA57, 0xBE8B, 0x7F99, 0xD093, 0xAA56, 0x7B2B, 0xE8CF,
    0x9951, 0x71E6, 0x021E, 0x8C39, 0x640C, 0x1B88, 0x83AB, 0x5213, 0x3403, 0x8019,
    0x3CA1, 0x4A88, 0x81C4, 0x2487, 0x5E1E, 0x88B7, 0x0ABA, 0x6DDE, 0x94C3, 0xF04B,
    0x7909, 0xA57F, 0xD65B, 0x7F09, 0xBA48, 0xBE0F, 0x7F80, 0xD248, 0xA885, 0x7A4B,
    0xEC7D, 0x96C5, 0x6F88, 0x07C0, 0x89B0, 0x5F99, 0x22D7, 0x81FB, 0x4B21, 0x3C7D,
    0x801D, 0x3300, 0x5373, 0x844B, 0x1849, 0x6692, 0x8E70, 0xFC3B, 0x74DA, 0x9E2B,
    0xE02E, 0x7D7E, 0xB2D2, 0xC585, 0x7FF4, 0xCB74, 0xADA0, 0x7BFD, 0xE6E6, 0x99C2,
    0x71AF, 0x03CB, 0x8B06, 0x6172, 0x20AD, 0x8249, 0x4C03, 0x3C06, 0x801E, 0x326D,
    0x545A, 0x84C2, 0x15FC, 0x6849, 0x9016, 0xF82D, 0x76AA, 0xA19B, 0xDA9E, 0x7E96,
    0xB874, 0xBEF5, 0x7F7E, 0xD372, 0xA6CB, 0x7934, 0xF120, 0x9390, 0x6BF2, 0x0FD4,
    0x8678, 0x585E, 0x2DCC, 0x8062, 0x3F81, 0x4940, 0x81CA, 0x22BC, 0x6082, 0x8ABD,
    0x03B8, 0x7217, 0x9AD2, 0xE44D, 0x7CD5, 0xB12D, 0xC667, 0x7FF3, 0xCC88, 0xABE7,
    0x7B1E, 0xEB42, 0x9689, 0x6E80, 0x0B76, 0x87BE, 0x5AC6, 0x2B1E, 0x8095, 0x4117,
    0x4829, 0x81A8, 0x2306, 0x60A5, 0x8B08, 0x027C, 0x72DF, 0x9C38, 0xE19B, 0x7D84,
    0xB433, 0xC298, 0x7FBB, 0xD173, 0xA798, 0x793B, 0xF20D, 0x9289, 0x6A51, 0x13CA,
    0x84FC, 0x53E6, 0x3453, 0x8004, 0x3770, 0x5153, 0x8420, 0x16DF, 0x68A7, 0x9127,
    0xF47D, 0x7887, 0xA64E, 0xD2C3, 0x7FAA, 0xC226, 0xB432, 0x7D68, 0xE2B9, 0x9B1D,
    0x71C4, 0x05A8, 0x897D, 0x5D7B, 0x2858, 0x80C9, 0x41F6, 0x481F, 0x81CE, 0x2138,
    0x627A, 0x8C9F, 0xFDBC, 0x7547, 0xA089, 0xDA3F, 0x7EEA, 0xBC1B, 0xB994, 0x7E7C,
    0xDD3E, 0x9E67, 0x73DE, 0x0159, 0x8B01, 0x5FC7, 0x2586, 0x8116, 0x43B8, 0x46C8,
    0x819E, 0x21E8, 0x6250, 0x8CB4, 0xFD19, 0x75B5, 0xA191, 0xD859, 0x7F35, 0xBE92,
    0xB6D1, 0x7DDA, 0xE157, 0x9B6F, 0x7198, 0x06EF, 0x88AF, 0x5B5A, 0x2C19, 0x8057,
    0x3CF2, 0x4D89, 0x834B, 0x18F8, 0x6833, 0x9170, 0xF295, 0x7996, 0xA9A7, 0xCD3C,
    0x7FFB, 0xC9DE, 0xAC5E, 0x7AA4, 0xEF39, 0x9315, 0x69E5, 0x164F, 0x83DB, 0x4F28,
    0x3B7A, 0x8042, 0x2CD1, 0x5B2C, 0x88CB, 0x060B, 0x724A, 0x9CD0, 0xDE84, 0x7E78,
    0xBA87, 0xBA11, 0x7E60, 0xDF2B, 0x9C4F, 0x71DA, 0x0734, 0x884A, 0x59FA, 0x2EB4,
    0x8021, 0x38FC, 0x51AF, 0x84D2, 0x1217, 0x6C8B, 0x960C, 0xE92F, 0x7C6A, 0xB238,
    0xC273, 0x7F86, 0xD68F, 0xA1EE, 0x755F, 0xFF61, 0x8B1F, 0x5EDA, 0x2870, 0x808F,
    0x3E32, 0x4D61, 0x8387, 0x16C0, 0x6A2F, 0x93E3, 0xECB1, 0x7BA2, 0xB008, 0xC48E,
    0x7FAE, 0xD509, 0xA2C4, 0x75B4, 0xFEEF, 0x8B25, 0x5EA2, 0x291E, 0x8076, 0x3CE2,
    0x4EDF, 0x8414, 0x1421, 0x6BDB, 0x95C4, 0xE8EB, 0x7CA8, 0xB3AD, 0xC02E, 0x7F30,
    0xDA83, 0x9EA8, 0x72FA, 0x05DD, 0x885A, 0x5945, 0x30B4, 0x8007, 0x34EF, 0x55F4,
    0x86D8, 0x0A28, 0x711C, 0x9C2C, 0xDDFF, 0x7EC6, 0xBD9E, 0xB5C4, 0x7D21, 0xE744,
    0x966D, 0x6C30, 0x1419, 0x83ED, 0x4DDB, 0x3EA2, 0x80B9, 0x25BD, 0x6188, 0x8D65,
    0xF8BF, 0x7854, 0xA889, 0xCC7E, 0x7FFD, 0xCEE0, 0xA69E, 0x775C, 0xFBA5, 0x8C0E,
    0x5F5B, 0x2924, 0x805F, 0x3AE9, 0x5179, 0x8544, 0x0EA2, 0x6F4A, 0x9A48, 0xE044,
    0x7E8A, 0xBCD6, 0xB5EF, 0x7D05, 0xE879, 0x9556, 0x6ABE, 0x176D, 0x82FC, 0x49FD,
    0x4364, 0x8189, 0x1F0B, 0x6652, 0x915F, 0xEFAF, 0x7B51, 0xB084, 0xC268, 0x7F4F,
    0xDACF, 0x9D89, 0x718C, 0x0A75, 0x8657, 0x53C5, 0x38CF, 0x8042, 0x2A03, 0x5F42,
    0x8C57, 0xFA1D, 0x7837, 0xA910, 0xCAE2, 0x7FEE, 0xD273, 0xA32F, 0x7517, 0x029E,
    0x88E3, 0x5914, 0x3292, 0x8004, 0x2FD6, 0x5B3A, 0x8A12, 0xFF59, 0x7671, 0xA5C1,
    0xCEC9, 0x7FFE, 0xCF1B, 0xA577, 0x763F, 0x0000,
};
