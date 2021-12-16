// Julian Ogata
// 11/20/2021
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


#ifndef mem_h
#define mem_h

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <utility>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>

#define ARGC_ERROR 1
#define FILE_ERROR 2
#define BUFLEN 256
#define FRAME_SIZE  256
#define TLB_SIZE 16


class VirtualMemory{
    public:
        VirtualMemory(){}
        ~VirtualMemory(){}

        unsigned getpage(unsigned x) { return (0xff00 & x) >> 8; }
        unsigned getoffset(unsigned x) { return (0xff & x); }
        unsigned getbin(unsigned x) { return (0xff00 & x);  }

        void storeaddresses(unsigned frame){
            char buf[BUFLEN];
            unsigned logic_add, offset, page, physical_add;
            unsigned phys_add, value, virt_add;
            info x;

            FILE* fadd = fopen("addresses.txt", "r");    // open file addresses.txt  (contains the logical addresses)
                if (fadd == NULL) { fprintf(stderr, "Could not open file: 'addresses.txt'\n");  exit(FILE_ERROR);  } std::ofstream f;
            FILE* fcorr = fopen("correct.txt", "r");     // contains the logical and physical address, and its value
                if (fcorr == NULL) { fprintf(stderr, "Could not open file: 'correct.txt'\n");  exit(FILE_ERROR);  }

            // Loop amount of frames and store in vector of struct Info
            while(frame < 40){
                fscanf(fadd, "%d", &logic_add);  // read from file address.txt
                fscanf(fcorr, "%s %s %d %s %s %d %s %d", buf, buf, &virt_add,
                    buf, buf, &phys_add, buf, &value);  // read from file correct.txt
                    
                    // From address.txt
                    page = getpage(logic_add);
                    offset = getoffset(logic_add);
                    physical_add = (frame) * FRAME_SIZE + offset;
                    


                // Allocate struct
                x.logic_add_ = logic_add;
                x.page_ = page; 
                x.offset_ = offset; 
                x.physical_add_ = physical_add;
                x.virt_add_ = virt_add;
                x.phys_add_ = phys_add;
                x.value_ = value;
                x.frame_ = frame;
                
                // Push struct into vector addresses to store;
                addresses_.push_back(x);
                
                // Print Info
                printf("\nINFO:\n\tPage: %d\n\toffset %d\n\tPhysical: %d\n\tVirtual: %d\n\tPhys: %d\n\tValue: %d\n\tFrame: %d\n",
                    addresses_.at(frame).page_, addresses_.at(frame).offset_, addresses_.at(frame).physical_add_,
                    addresses_.at(frame).virt_add_, addresses_.at(frame).phys_add_, addresses_.at(frame).value_,
                    addresses_.at(frame).frame_);

                frame++;
            }
            printf("Finished Storing addresses from addresses.txt\n");
            fclose(fcorr);
            fclose(fadd);
        }

    //-------------------------------------------
    // MODIFIED
    //-------------------------------------------
        // Checks Addresses with tlb and page_tables
        void process(unsigned frame){
            while(frame < 40){
                checkaddress(addresses_.at(frame).page_, frame);
                updatetlb(frame);
                updatetlb2(frame);      // ADDED
                assert(addresses_.at(frame).physical_add_ == addresses_.at(frame).phys_add_);
                frame++;
            }
        }
    //-------------------------------------------

        // Creates page table using stored address info
        void createpagetable(unsigned frame){
            for(std::vector<struct info>::iterator i = addresses_.begin(); i  != addresses_.end(); i++){
                page_table_[frame] = std::make_pair(i->page_, frame);
                frame++;
            }
            printf("Finished Creating Page Table\n");
        }
        // NOT USED. Updates frame in page table
        void updatepagetable(unsigned page, unsigned frame){
            for(int i = 0; i < BUFLEN;i++){
                if(page_table_[i].first == page){
                    printf("PAGE FOUND IN PAGE_TABLE!\nUpdating...\n");
                    page_table_[i].second = frame;
                }
            }
        }


        // Creates TLB
        void createtlb(unsigned frame){
            for(int i = 0; i < TLB_SIZE; i++){
                tlb_[i] = page_table_[i];
            }
        }
        // Updates tlb to the next page
        void updatetlb(unsigned frame){
            for(int i = 0; i < TLB_SIZE; i++){
                std::pair<unsigned, unsigned> temp = tlb_[i+1];
                tlb_[i] = temp;
            }
            tlb_[16] = page_table_[frame+16];
        }

    //-------------------------------------------
    // ADDED
    //-------------------------------------------
        // Creates TLB2
        void createtlb2(unsigned frame){
            for(int i = 0; i < 64; i++){
                tlb2_[i] = page_table_[i];
            }
        }
        // Updates tlb to the next page
        void updatetlb2(unsigned frame){
            for(int i = 0; i < 64; i++){
                std::pair<unsigned, unsigned> temp = tlb2_[i+1];
                tlb2_[i] = temp;
            }
            tlb2_[64] = page_table_[frame+64];
        }
        
    //-------------------------------------------

        // Checks tlb for page and same physical address
        bool tlbhit(unsigned page, unsigned frame){
            for(int i = 0; i < TLB_SIZE ; i++){
                if(page == tlb_[i].first && addresses_.at(frame).physical_add_ == addresses_.at(frame).phys_add_){
                    printf("HIT IN TLB 1!\n");
                    return true;
                }
                else if(page == tlb2_[i].first && addresses_.at(frame).physical_add_ == addresses_.at(frame).phys_add_){
                    printf("HIT IN TLB 2!\n");
                    return true;
                }
                else{continue;}
            }
            return false;
        }

        // Searches bin for value then updates address info and page table
        void searchbin(unsigned page, unsigned frame){
            FILE* fbin = fopen("BACKING_STORE.bin", "r");    // open file BACKING_STORE.bin
                if (fbin == NULL) { fprintf(stderr, "Could not open file: 'BACKING_STORAGE.bin'\n");  exit(FILE_ERROR);  }

            // Find value in bin 
            fseek(fbin, addresses_.at(frame).value_ , SEEK_SET);
            bin_ = ftell(fbin);
            fscanf(fbin,"%u", &bin_);
            //If the value from bin matches the value in addresses, update
            if(bin_ == addresses_.at(frame).value_){
                printf("Values Match! Updating address...\n");
                addresses_.at(frame).logic_add_ = addresses_.at(frame).virt_add_;
                addresses_.at(frame).physical_add_ = addresses_.at(frame).phys_add_;
                addresses_.at(frame).page_   = getpage(addresses_.at(frame).logic_add_);
                addresses_.at(frame).offset_ = getoffset(addresses_.at(frame).logic_add_);
                page_table_[frame].first = addresses_.at(frame).page_;
                printf("UPDATED!\nPage # %d\nFrame # %d\n\n", page_table_[frame].first, page_table_[frame].second);
            }
            else{
                printf("No Match...\n\n");
                exit(1);
            }
        }

        // Checks each stored address info
        void checkaddress(unsigned page, unsigned frame){
            if(tlbhit(page, frame)){
                printf("TLB HIT: page: %d\n", page);
            }
            else{
                printf("TLB MISS... Searching Page Table...\n");
                if(page == page_table_[frame].first && addresses_.at(frame).physical_add_ == addresses_.at(frame).phys_add_){
                    printf("Page Found!\n");
                }
                else{
                    printf("Page not found... Searching Bin...\n");
                    searchbin(page, frame);
                }
            }
        }


    private:
        struct info {
            unsigned logic_add_;
            unsigned page_; 
            unsigned offset_; 
            unsigned physical_add_;
            unsigned virt_add_;
            unsigned phys_add_;
            unsigned value_;
            unsigned frame_;
        };
        unsigned   bin_;
        std::vector<info> addresses_;
        std::pair<unsigned, unsigned> tlb_[TLB_SIZE];    
        std::pair<unsigned, unsigned> tlb2_[64];            // TLB array
        std::pair<unsigned, unsigned> page_table_[BUFLEN];         // Page Table array
};

#endif