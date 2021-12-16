// Julian Ogata
// 11/20/2021
//
// Modified for final: 12/16/2021
//
// Included files:
//      mem_manager.cpp
//      mem.h 
//
//  Based off of William McCarthy's Virtual Memory Skeleton Code
//
//  The output is listed in mem_manager.cpp.
//  Only a certain number of output is listed due to terminal limits
//

#include "mem.h"

VirtualMemory mem;

int main(int argc, char const *argv[]){
    unsigned frame = 0;
    mem.storeaddresses(frame);
    mem.createpagetable(frame);
    mem.createtlb(frame);
    mem.createtlb2(frame);  // ADDED

    mem.process(frame);    

    printf("All Asserts Passed\n");
    return 0;
}

// FOR FINAL
// WITH TLB2!!!! (Up to 40 due to terminal output limitations) 
//
// osc@ubuntu:~/final-src-osc10e/Hw/Virtual_Mem$ ./mem_manager 

// INFO:
//         Page: 66
//         offset 20
//         Physical: 20
//         Virtual: 16916
//         Phys: 20
//         Value: 0
//         Frame: 0

// INFO:
//         Page: 244
//         offset 29
//         Physical: 285
//         Virtual: 62493
//         Phys: 285
//         Value: 0
//         Frame: 1

// INFO:
//         Page: 117
//         offset 246
//         Physical: 758
//         Virtual: 30198
//         Phys: 758
//         Value: 29
//         Frame: 2

// INFO:
//         Page: 209
//         offset 179
//         Physical: 947
//         Virtual: 53683
//         Phys: 947
//         Value: 108
//         Frame: 3

// INFO:
//         Page: 156
//         offset 249
//         Physical: 1273
//         Virtual: 40185
//         Phys: 1273
//         Value: 0
//         Frame: 4

// INFO:
//         Page: 112
//         offset 109
//         Physical: 1389
//         Virtual: 28781
//         Phys: 1389
//         Value: 0
//         Frame: 5

// INFO:
//         Page: 95
//         offset 142
//         Physical: 1678
//         Virtual: 24462
//         Phys: 1678
//         Value: 23
//         Frame: 6

// INFO:
//         Page: 189
//         offset 15
//         Physical: 1807
//         Virtual: 48399
//         Phys: 1807
//         Value: 67
//         Frame: 7

// INFO:
//         Page: 253
//         offset 47
//         Physical: 2095
//         Virtual: 64815
//         Phys: 2095
//         Value: 75
//         Frame: 8

// INFO:
//         Page: 71
//         offset 119
//         Physical: 2423
//         Virtual: 18295
//         Phys: 2423
//         Value: -35
//         Frame: 9

// INFO:
//         Page: 47
//         offset 186
//         Physical: 2746
//         Virtual: 12218
//         Phys: 2746
//         Value: 11
//         Frame: 10

// INFO:
//         Page: 88
//         offset 232
//         Physical: 3048
//         Virtual: 22760
//         Phys: 3048
//         Value: 0
//         Frame: 11

// INFO:
//         Page: 226
//         offset 126
//         Physical: 3198
//         Virtual: 57982
//         Phys: 3198
//         Value: 56
//         Frame: 12

// INFO:
//         Page: 109
//         offset 62
//         Physical: 3390
//         Virtual: 27966
//         Phys: 3390
//         Value: 27
//         Frame: 13

// INFO:
//         Page: 214
//         offset 110
//         Physical: 3694
//         Virtual: 54894
//         Phys: 3694
//         Value: 53
//         Frame: 14

// INFO:
//         Page: 152
//         offset 17
//         Physical: 3857
//         Virtual: 38929
//         Phys: 3857
//         Value: 0
//         Frame: 15

// INFO:
//         Page: 128
//         offset 97
//         Physical: 4193
//         Virtual: 32865
//         Phys: 4193
//         Value: 0
//         Frame: 16

// INFO:
//         Page: 250
//         offset 243
//         Physical: 4595
//         Virtual: 64243
//         Phys: 4595
//         Value: -68
//         Frame: 17

// INFO:
//         Page: 9
//         offset 11
//         Physical: 4619
//         Virtual: 2315
//         Phys: 4619
//         Value: 66
//         Frame: 18

// INFO:
//         Page: 251
//         offset 198
//         Physical: 5062
//         Virtual: 64454
//         Phys: 5062
//         Value: 62
//         Frame: 19

// INFO:
//         Page: 215
//         offset 1
//         Physical: 5121
//         Virtual: 55041
//         Phys: 5121
//         Value: 0
//         Frame: 20

// INFO:
//         Page: 72
//         offset 201
//         Physical: 5577
//         Virtual: 18633
//         Phys: 5577
//         Value: 0
//         Frame: 21

// INFO:
//         Page: 56
//         offset 221
//         Physical: 5853
//         Virtual: 14557
//         Phys: 5853
//         Value: 0
//         Frame: 22

// INFO:
//         Page: 238
//         offset 78
//         Physical: 5966
//         Virtual: 61006
//         Phys: 5966
//         Value: 59
//         Frame: 23

// INFO:
//         Page: 244
//         offset 151
//         Physical: 6295
//         Virtual: 62615
//         Phys: 407
//         Value: 37
//         Frame: 24

// INFO:
//         Page: 29
//         offset 167
//         Physical: 6567
//         Virtual: 7591
//         Phys: 6311
//         Value: 105
//         Frame: 25

// INFO:
//         Page: 252
//         offset 235
//         Physical: 6891
//         Virtual: 64747
//         Phys: 6635
//         Value: 58
//         Frame: 26

// INFO:
//         Page: 26
//         offset 71
//         Physical: 6983
//         Virtual: 6727
//         Phys: 6727
//         Value: -111
//         Frame: 27

// INFO:
//         Page: 126
//         offset 59
//         Physical: 7227
//         Virtual: 32315
//         Phys: 6971
//         Value: -114
//         Frame: 28

// INFO:
//         Page: 236
//         offset 229
//         Physical: 7653
//         Virtual: 60645
//         Phys: 7397
//         Value: 0
//         Frame: 29

// INFO:
//         Page: 24
//         offset 164
//         Physical: 7844
//         Virtual: 6308
//         Phys: 7588
//         Value: 0
//         Frame: 30

// INFO:
//         Page: 178
//         offset 120
//         Physical: 8056
//         Virtual: 45688
//         Phys: 7800
//         Value: 0
//         Frame: 31

// INFO:
//         Page: 3
//         offset 201
//         Physical: 8393
//         Virtual: 969
//         Phys: 8137
//         Value: 0
//         Frame: 32

// INFO:
//         Page: 159
//         offset 187
//         Physical: 8635
//         Virtual: 40891
//         Phys: 8379
//         Value: -18
//         Frame: 33

// INFO:
//         Page: 192
//         offset 142
//         Physical: 8846
//         Virtual: 49294
//         Phys: 8590
//         Value: 48
//         Frame: 34

// INFO:
//         Page: 160
//         offset 158
//         Physical: 9118
//         Virtual: 41118
//         Phys: 8862
//         Value: 40
//         Frame: 35

// INFO:
//         Page: 83
//         offset 147
//         Physical: 9363
//         Virtual: 21395
//         Phys: 9107
//         Value: -28
//         Frame: 36

// INFO:
//         Page: 23
//         offset 203
//         Physical: 9675
//         Virtual: 6091
//         Phys: 9419
//         Value: -14
//         Frame: 37

// INFO:
//         Page: 127
//         offset 29
//         Physical: 9757
//         Virtual: 32541
//         Phys: 9501
//         Value: 0
//         Frame: 38

// INFO:
//         Page: 69
//         offset 1
//         Physical: 9985
//         Virtual: 17665
//         Phys: 9729
//         Value: 0
//         Frame: 39
// Finished Storing addresses from addresses.txt
// Finished Creating Page Table
// HIT IN TLB 1!
// TLB HIT: page: 66
// HIT IN TLB 1!
// TLB HIT: page: 244
// HIT IN TLB 1!
// TLB HIT: page: 117
// HIT IN TLB 1!
// TLB HIT: page: 209
// HIT IN TLB 1!
// TLB HIT: page: 156
// HIT IN TLB 1!
// TLB HIT: page: 112
// HIT IN TLB 1!
// TLB HIT: page: 95
// HIT IN TLB 1!
// TLB HIT: page: 189
// HIT IN TLB 1!
// TLB HIT: page: 253
// HIT IN TLB 1!
// TLB HIT: page: 71
// HIT IN TLB 1!
// TLB HIT: page: 47
// HIT IN TLB 1!
// TLB HIT: page: 88
// HIT IN TLB 1!
// TLB HIT: page: 226
// HIT IN TLB 1!
// TLB HIT: page: 109
// HIT IN TLB 1!
// TLB HIT: page: 214
// HIT IN TLB 1!
// TLB HIT: page: 152
// HIT IN TLB 2!
// TLB HIT: page: 128
// HIT IN TLB 2!
// TLB HIT: page: 250
// HIT IN TLB 2!
// TLB HIT: page: 9
// HIT IN TLB 2!
// TLB HIT: page: 251
// HIT IN TLB 2!
// TLB HIT: page: 215
// HIT IN TLB 2!
// TLB HIT: page: 72
// HIT IN TLB 2!
// TLB HIT: page: 56
// HIT IN TLB 2!
// TLB HIT: page: 238
// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 244
// Frame # 24

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 29
// Frame # 25

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 252
// Frame # 26

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 26
// Frame # 27

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 126
// Frame # 28

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 236
// Frame # 29

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 24
// Frame # 30

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 178
// Frame # 31

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 3
// Frame # 32

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 159
// Frame # 33

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 192
// Frame # 34

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 160
// Frame # 35

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 83
// Frame # 36

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 23
// Frame # 37

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 127
// Frame # 38

// TLB MISS... Searching Page Table...
// Page not found... Searching Bin...
// Values Match! Updating address...
// UPDATED!
// Page # 69
// Frame # 39

// All Asserts Passed