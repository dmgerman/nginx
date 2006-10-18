begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_core.h>
end_include

begin_comment
comment|/*  * The code and lookup table is based on the algorithm  * described at http://www.w3.org/TR/PNG/  */
end_comment

begin_decl_stmt
DECL|variable|ngx_crc32_table
name|uint32_t
name|ngx_crc32_table
index|[]
init|=
block|{
literal|0x00000000
block|,
literal|0x77073096
block|,
literal|0xee0e612c
block|,
literal|0x990951ba
block|,
literal|0x076dc419
block|,
literal|0x706af48f
block|,
literal|0xe963a535
block|,
literal|0x9e6495a3
block|,
literal|0x0edb8832
block|,
literal|0x79dcb8a4
block|,
literal|0xe0d5e91e
block|,
literal|0x97d2d988
block|,
literal|0x09b64c2b
block|,
literal|0x7eb17cbd
block|,
literal|0xe7b82d07
block|,
literal|0x90bf1d91
block|,
literal|0x1db71064
block|,
literal|0x6ab020f2
block|,
literal|0xf3b97148
block|,
literal|0x84be41de
block|,
literal|0x1adad47d
block|,
literal|0x6ddde4eb
block|,
literal|0xf4d4b551
block|,
literal|0x83d385c7
block|,
literal|0x136c9856
block|,
literal|0x646ba8c0
block|,
literal|0xfd62f97a
block|,
literal|0x8a65c9ec
block|,
literal|0x14015c4f
block|,
literal|0x63066cd9
block|,
literal|0xfa0f3d63
block|,
literal|0x8d080df5
block|,
literal|0x3b6e20c8
block|,
literal|0x4c69105e
block|,
literal|0xd56041e4
block|,
literal|0xa2677172
block|,
literal|0x3c03e4d1
block|,
literal|0x4b04d447
block|,
literal|0xd20d85fd
block|,
literal|0xa50ab56b
block|,
literal|0x35b5a8fa
block|,
literal|0x42b2986c
block|,
literal|0xdbbbc9d6
block|,
literal|0xacbcf940
block|,
literal|0x32d86ce3
block|,
literal|0x45df5c75
block|,
literal|0xdcd60dcf
block|,
literal|0xabd13d59
block|,
literal|0x26d930ac
block|,
literal|0x51de003a
block|,
literal|0xc8d75180
block|,
literal|0xbfd06116
block|,
literal|0x21b4f4b5
block|,
literal|0x56b3c423
block|,
literal|0xcfba9599
block|,
literal|0xb8bda50f
block|,
literal|0x2802b89e
block|,
literal|0x5f058808
block|,
literal|0xc60cd9b2
block|,
literal|0xb10be924
block|,
literal|0x2f6f7c87
block|,
literal|0x58684c11
block|,
literal|0xc1611dab
block|,
literal|0xb6662d3d
block|,
literal|0x76dc4190
block|,
literal|0x01db7106
block|,
literal|0x98d220bc
block|,
literal|0xefd5102a
block|,
literal|0x71b18589
block|,
literal|0x06b6b51f
block|,
literal|0x9fbfe4a5
block|,
literal|0xe8b8d433
block|,
literal|0x7807c9a2
block|,
literal|0x0f00f934
block|,
literal|0x9609a88e
block|,
literal|0xe10e9818
block|,
literal|0x7f6a0dbb
block|,
literal|0x086d3d2d
block|,
literal|0x91646c97
block|,
literal|0xe6635c01
block|,
literal|0x6b6b51f4
block|,
literal|0x1c6c6162
block|,
literal|0x856530d8
block|,
literal|0xf262004e
block|,
literal|0x6c0695ed
block|,
literal|0x1b01a57b
block|,
literal|0x8208f4c1
block|,
literal|0xf50fc457
block|,
literal|0x65b0d9c6
block|,
literal|0x12b7e950
block|,
literal|0x8bbeb8ea
block|,
literal|0xfcb9887c
block|,
literal|0x62dd1ddf
block|,
literal|0x15da2d49
block|,
literal|0x8cd37cf3
block|,
literal|0xfbd44c65
block|,
literal|0x4db26158
block|,
literal|0x3ab551ce
block|,
literal|0xa3bc0074
block|,
literal|0xd4bb30e2
block|,
literal|0x4adfa541
block|,
literal|0x3dd895d7
block|,
literal|0xa4d1c46d
block|,
literal|0xd3d6f4fb
block|,
literal|0x4369e96a
block|,
literal|0x346ed9fc
block|,
literal|0xad678846
block|,
literal|0xda60b8d0
block|,
literal|0x44042d73
block|,
literal|0x33031de5
block|,
literal|0xaa0a4c5f
block|,
literal|0xdd0d7cc9
block|,
literal|0x5005713c
block|,
literal|0x270241aa
block|,
literal|0xbe0b1010
block|,
literal|0xc90c2086
block|,
literal|0x5768b525
block|,
literal|0x206f85b3
block|,
literal|0xb966d409
block|,
literal|0xce61e49f
block|,
literal|0x5edef90e
block|,
literal|0x29d9c998
block|,
literal|0xb0d09822
block|,
literal|0xc7d7a8b4
block|,
literal|0x59b33d17
block|,
literal|0x2eb40d81
block|,
literal|0xb7bd5c3b
block|,
literal|0xc0ba6cad
block|,
literal|0xedb88320
block|,
literal|0x9abfb3b6
block|,
literal|0x03b6e20c
block|,
literal|0x74b1d29a
block|,
literal|0xead54739
block|,
literal|0x9dd277af
block|,
literal|0x04db2615
block|,
literal|0x73dc1683
block|,
literal|0xe3630b12
block|,
literal|0x94643b84
block|,
literal|0x0d6d6a3e
block|,
literal|0x7a6a5aa8
block|,
literal|0xe40ecf0b
block|,
literal|0x9309ff9d
block|,
literal|0x0a00ae27
block|,
literal|0x7d079eb1
block|,
literal|0xf00f9344
block|,
literal|0x8708a3d2
block|,
literal|0x1e01f268
block|,
literal|0x6906c2fe
block|,
literal|0xf762575d
block|,
literal|0x806567cb
block|,
literal|0x196c3671
block|,
literal|0x6e6b06e7
block|,
literal|0xfed41b76
block|,
literal|0x89d32be0
block|,
literal|0x10da7a5a
block|,
literal|0x67dd4acc
block|,
literal|0xf9b9df6f
block|,
literal|0x8ebeeff9
block|,
literal|0x17b7be43
block|,
literal|0x60b08ed5
block|,
literal|0xd6d6a3e8
block|,
literal|0xa1d1937e
block|,
literal|0x38d8c2c4
block|,
literal|0x4fdff252
block|,
literal|0xd1bb67f1
block|,
literal|0xa6bc5767
block|,
literal|0x3fb506dd
block|,
literal|0x48b2364b
block|,
literal|0xd80d2bda
block|,
literal|0xaf0a1b4c
block|,
literal|0x36034af6
block|,
literal|0x41047a60
block|,
literal|0xdf60efc3
block|,
literal|0xa867df55
block|,
literal|0x316e8eef
block|,
literal|0x4669be79
block|,
literal|0xcb61b38c
block|,
literal|0xbc66831a
block|,
literal|0x256fd2a0
block|,
literal|0x5268e236
block|,
literal|0xcc0c7795
block|,
literal|0xbb0b4703
block|,
literal|0x220216b9
block|,
literal|0x5505262f
block|,
literal|0xc5ba3bbe
block|,
literal|0xb2bd0b28
block|,
literal|0x2bb45a92
block|,
literal|0x5cb36a04
block|,
literal|0xc2d7ffa7
block|,
literal|0xb5d0cf31
block|,
literal|0x2cd99e8b
block|,
literal|0x5bdeae1d
block|,
literal|0x9b64c2b0
block|,
literal|0xec63f226
block|,
literal|0x756aa39c
block|,
literal|0x026d930a
block|,
literal|0x9c0906a9
block|,
literal|0xeb0e363f
block|,
literal|0x72076785
block|,
literal|0x05005713
block|,
literal|0x95bf4a82
block|,
literal|0xe2b87a14
block|,
literal|0x7bb12bae
block|,
literal|0x0cb61b38
block|,
literal|0x92d28e9b
block|,
literal|0xe5d5be0d
block|,
literal|0x7cdcefb7
block|,
literal|0x0bdbdf21
block|,
literal|0x86d3d2d4
block|,
literal|0xf1d4e242
block|,
literal|0x68ddb3f8
block|,
literal|0x1fda836e
block|,
literal|0x81be16cd
block|,
literal|0xf6b9265b
block|,
literal|0x6fb077e1
block|,
literal|0x18b74777
block|,
literal|0x88085ae6
block|,
literal|0xff0f6a70
block|,
literal|0x66063bca
block|,
literal|0x11010b5c
block|,
literal|0x8f659eff
block|,
literal|0xf862ae69
block|,
literal|0x616bffd3
block|,
literal|0x166ccf45
block|,
literal|0xa00ae278
block|,
literal|0xd70dd2ee
block|,
literal|0x4e048354
block|,
literal|0x3903b3c2
block|,
literal|0xa7672661
block|,
literal|0xd06016f7
block|,
literal|0x4969474d
block|,
literal|0x3e6e77db
block|,
literal|0xaed16a4a
block|,
literal|0xd9d65adc
block|,
literal|0x40df0b66
block|,
literal|0x37d83bf0
block|,
literal|0xa9bcae53
block|,
literal|0xdebb9ec5
block|,
literal|0x47b2cf7f
block|,
literal|0x30b5ffe9
block|,
literal|0xbdbdf21c
block|,
literal|0xcabac28a
block|,
literal|0x53b39330
block|,
literal|0x24b4a3a6
block|,
literal|0xbad03605
block|,
literal|0xcdd70693
block|,
literal|0x54de5729
block|,
literal|0x23d967bf
block|,
literal|0xb3667a2e
block|,
literal|0xc4614ab8
block|,
literal|0x5d681b02
block|,
literal|0x2a6f2b94
block|,
literal|0xb40bbe37
block|,
literal|0xc30c8ea1
block|,
literal|0x5a05df1b
block|,
literal|0x2d02ef8d
block|}
decl_stmt|;
end_decl_stmt

end_unit

