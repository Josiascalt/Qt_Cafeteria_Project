/*#include <cassert>
#include <array>

#include "file_handler.h"

using namespace std;
using namespace file_handler;

namespace testing {
    namespace file_handler_testing {//Test the methods Write, Read and GetSize with only the required arguments
        void Test1(BinaryFile<int>* bf, TextFile* tf) {
            
            assert(bf -> GetSize() == 0ull);
            assert(tf -> GetSize() == 0ull);
            
            int a = 1;
            int b = 3;
            int c = 5;
            
            bf->Write(&a);
            assert(bf -> GetSize() == 1ull);
            bf->Write(&b);
            assert(bf -> GetSize() == 2ull);
            bf->Write(&c);
            assert(bf -> GetSize() == 3ull);
            
            tf->PutInStream(&a);
            assert(tf -> GetSize() == 1ull);
            tf->PutInStream(&b);
            assert(tf -> GetSize() == 2ull);
            tf->PutInStream(&c);
            assert(tf -> GetSize() == 3ull);
            
            //testing binary items
            int bi0;
            int bi1;
            int bi2;
            
            bf->Read(&bi0);
            bf->Read(&bi1);
            bf->Read(&bi2);
            
            assert(bi0 == 1ull);
            assert(bi1 == 3ull);
            assert(bi2 == 5ull);
            
            //testing text items
            auto ti0 = tf->Substr();
            auto ti1 = tf->Substr();
            auto ti2 = tf->Substr();
            assert(ti0 == "1" && ti0.size() == 1ull);
            assert(ti1 == "3" && ti1.size() == 1ull);
            assert(ti2 == "5" && ti2.size() == 1ull);
        }

        //Test the method Read with only <count>
        void Test2(BinaryFile<int>* bf, TextFile* tf) {
            assert(bf->GetSize() == 3ull);
            assert(tf->GetSize() == 3ull);
            
            //reading binary items
            int bi0 = 100;
            
            bf->Read(&bi0);
            assert(bi0 == 1);
            assert(bi0 != 100);
            
            int bi1;
            
            bf->Read(&bi1);
            assert(bi0 != bi1);
            assert(bi1 == 3);
            
            int bi2 = 0;
            bf->Read(&bi2, 0);
            assert(bi2 == 0);
            assert(bi2 != -1);
            
            int bi3;
            bf->Read(&bi3);
            assert(bi3 == 5);
            assert(bi3 != 3);
            assert(bi3 != bi0);
            
            int bi4;
            bf->Read(&bi4);
            assert(bi4 == bi0);
            assert(bi4 != bi1);
            assert(bi4 != bi2);
            assert(bi4 != bi3);
            assert(bi4 == 1);
            assert(bi4 != 3);
            assert(bi4 == (bi3 - 4));
            
            int bi5;
            bf->Read(&bi5, 1);
            assert(bi5 == 3);
            assert(bi5 == bi1);
            assert(bi5 == (bi4 + 2));
            
            int bi6 = 0;
            bf->Read(&bi6, 0);
            assert(bi6 == 0);
            assert(bi6 == bi2);
            assert(bi6 == (bi0 - 1));
            assert(bi6 != bi5);
            
            std::array<int, 2ull> bi7 = {0,0};
            bf->Read(bi7.data(), 1);
            assert(bi7[0] == 5);
            assert(bi7[0] == bi3);
            assert(bi7[1] == 0);
            bf->Read(bi7.data(), 2);
            assert(bi7[0] == bi4);
            assert(bi7[0] != 5);
            assert(bi7[0] == 1);
            assert(bi7[1] == bi5);
            assert(bi7[1] != 0);
            assert(bi7[1] == 3);
            
            bf->Read(&bi7[1], 1);
            assert(bi7[1] == 5ull);
            assert(bi7[1] == bi3);
            
            
            assert(bf->GetSize() == 3ull);
            
            //reading text items
            
            auto ti0 = tf->Substr();
            assert(ti0 == "1"s);
            assert(!ti0.empty());
            
            auto ti1 = tf->Substr();
            assert(ti0 != ti1);
            assert(ti1 == "3"s);
            
            auto ti2 = tf->Substr(0);
            assert(ti2.empty());
            assert(ti2 != ti1 && ti2 != ti0);
            
            auto ti3 = tf->Substr();
            assert(ti3 == "5"s);
            assert(ti3.size() == 1);
            assert(!ti3.empty());
            
            auto ti4 = tf->Substr();
            assert(ti4 == ti0);
            assert(ti4 != ti1);
            assert(ti4 != ti2);
            assert(ti4 != ti3);
            assert(ti4 == "1"s);
            assert(ti4 != "3"s);
            assert(!ti4.empty());
            assert(ti4.size() == 1);
            
            auto ti5 = tf->Substr(1ull);
            assert(ti5 == "3"s);
            assert(ti5 == ti1);
            
            auto ti6 = tf->Substr(0);
            assert(ti6.empty());
            assert(ti6 == ""s);
            assert(ti6 == ti2);
            
            auto ti7 = tf->Substr(1);
            assert(ti7[0] == '5');
            assert(ti7.size() == 1ull);
            
            auto ti8 = tf->Substr(3ull);
            assert(ti8.size() == 3ull);
            assert(ti8 == "135"s);
            assert(ti8[0] == '1');
            assert(ti8[1] == '3');
            assert(ti8[2] == '5');
            assert(!ti8.empty());
            
            auto ti9 = tf->Substr(2ull);
            assert(ti9.size() == 2ull);
            assert(ti9 == "13"s);
            assert(ti9[0] == '1');
            assert(ti9[1] == '3');
            assert(!ti9.empty());
            
            auto ti10 = tf->Substr(1ull);
            assert(ti10.size() == 1ull);
            assert(!ti10.empty());
            assert(ti10 == "5"s);
            
            assert(tf->GetSize() == 3ull);
        }

        //Test the method Write with only <count>
        void Test3(BinaryFile<int>* bf, TextFile* tf) {
            assert(bf->GetSize() == 3ull);
            assert(tf->GetSize() == 3ull);
            
            //writing binary items
            {
                std::array<int, 10> items;
                int item_to_add = 7;
                
                bf->Write(&item_to_add);
                assert(bf->GetSize() == 4ull);
                
                bf->Read(items.data(), 1ull);
                assert(items[0] != 5);
                assert(items[0] == 7);
                assert(items[0] == item_to_add);
                
                bf->Read(items.data(), 4ull);
                assert(items[3] == item_to_add);
                
                bf->Write(items.data(), 4ull);
                assert(bf->GetSize() == 8ull);
                
                bf->Read(&items[4], 4ull);
                assert(items[4] == 1);
                assert(items[5] == 3);
                assert(items[6] == 5);
                assert(items[7] == 7);
                
                bf->Read(items.data(), 8ull);
                assert(items[4] == items[0]);
                assert(items[5] == items[1]);
                assert(items[6] == items[2]);
                assert(items[7] == items[3]);
                
                item_to_add = 9;
                bf->Write(&item_to_add, 1ull);
                assert(bf->GetSize() == 9ull);
                bf->Read(&items[8], 1ull);
                assert(items[8] == 9);
            }
            
            //writing text items
            {
                int item_to_add1 = 7;
                double item_to_add2 = 9;
                auto item_to_add3 = "11";
                auto item_to_add4 = "13"s;
                
                tf->PutInStream(&item_to_add1);
                assert(tf->GetSize() == 4ull);
                assert(tf->Substr() == "7"s);
                
                tf->PutInStream(&item_to_add2);
                assert(tf->GetSize() == 5ull);
                assert(tf->Substr() == "9"s);
                
                tf->PutInStream(&item_to_add3);
                assert(tf->GetSize() == 7ull);
                assert(tf->Substr() == "1"s);
                
                tf->PutInStream(&item_to_add4);
                assert(tf->GetSize() == 9ull);
                assert(tf->Substr(3ull) == "113"s);
                
                assert(tf->Substr(9ull) == "135791113"s);
            }
            
        }

        //Test the method Read using all the args
        void Test4(BinaryFile<int>* bf, TextFile* tf) {
            assert(bf->GetSize() == 9ull);
            assert(tf->GetSize() == 9ull);
            
            {
                std::array<int, 9> items;
                bf->Read(items.data(), 9ull, 0);
                assert(items[0] == 1);
                assert(items[1] == 3);
                assert(items[8] == 9);
                
                assert(items[5] == 3);
                bf->Read(&items[5], 1, 8);
                assert(items[5] == 9);
                assert(items[5] != 3);
                
                bf->Read(&items[5]);
                assert(items[5] == 1);
                assert(items[5] != 9);
                
                bf->Read(&items[5], 1);
                assert(items[5] == 3);
                assert(items[5] != 1);
                
                bf->Read(&items[0], 5ull, 4ull);
                assert(items[0] == 1);
                assert(items[1] == 3);
                assert(items[2] == 5);
                assert(items[3] == 7);
                assert(items[4] == 9);
                assert(items[4] == items[8]);
                
                bf->Read(&items[8], 0, 0);
                assert(items[8] == 9);
                assert(items[8] != 1);
                
                bf->Read(&items[8], 1ull, 0);
                assert(items[8] == 1);
                assert(items[8] != 9);
                
                bf->Read(&items[8], 1ull, 8ull);
                assert(items[8] == 9);
                assert(items[8] != 1);
            }
            
            {
                assert(tf->Substr(1, 0) == "1"s);
                
                assert(tf->Substr(0, 0).empty());
                
                std::string last_read_item;
                
                last_read_item = tf->Substr(1ull, 8ull);
                assert(last_read_item == "3"s);
                assert(last_read_item.size() == 1);
                
                last_read_item = tf->Substr(3ull, 4ull);
                assert(last_read_item == "911"s);
                assert(last_read_item.size() == 3);
                
                last_read_item = tf->Substr(9ull, 0);
                assert(last_read_item == "135791113"s);
                assert(last_read_item != "911"s);
                assert(last_read_item.size() == 9);
                
                last_read_item = tf->Substr(2ull);
                assert(last_read_item == "13"s);
                assert(last_read_item.size() == 2);
                
                last_read_item = tf->Substr(3ull);
                assert(last_read_item == "579"s);
                assert(last_read_item.size() == 3);
            }
        }

        //Test the method Read using all the args
        void Test5(BinaryFile<int>* bf, TextFile* tf) {
            assert(bf->GetSize() == 9ull);
            assert(tf->GetSize() == 9ull);
            //writing binary items
            {
                std::array<int, 10> items;
                int item_to_write;
                
                bf->Read(&items[0], 1ull, 1ull);
                assert(items[0] == 3);
                
                item_to_write = 2;
                bf->Write(&item_to_write, 1ull, 1ull);
                bf->Read(&items[0], 1ull, 1ull);
                assert(items[0] == 2);
                assert(items[0] == item_to_write);
                assert(bf->GetSize() == 9ull);
                
                item_to_write = 10;
                bf->Write(&item_to_write, 1ull, 9ull);
                bf->Read(&items[9], 1ull, 9ull);
                assert(items[9] == 10);
                assert(items[9] == item_to_write);
                assert(bf->GetSize() == 10ull);
                
                item_to_write = 8;
                bf->Write(&item_to_write, 1ull, 7ull);
                bf->Read(&items[1], 1ull, 7ull);
                assert(items[1] == 8);
                assert(items[1] == item_to_write);
                assert(bf->GetSize() == 10ull);
                
                items = {1,2,3,4,5};
                bf->Write(items.data(), 5ull, 0);
                bf->Read(&items[5], 5ull, 0);
                assert(items[5] == 1);
                assert(items[6] == 2);
                assert(items[7] == 3);
                assert(items[8] == 4);
                assert(items[9] == 5);
                assert(bf->GetSize() == 10ull);
                
                items = {6,7,8,9,10,11,12,13,14,15};
                bf->Write(items.data(), items.size(), 5ull);
                assert(bf->GetSize() == 15ull);
                
                std::array<int, 15> result;
                
                bf->Read(result.data(), result.size(), 0);
                assert(result[0] == 1);
                assert(result[14] == 15);
                assert(result[6] == 7);
                assert(result[11] == 12);
                
                item_to_write = 16;
                bf->Write(&item_to_write, 1);
                assert(bf->GetSize() == 16ull);
                bf->Read(&items[0], 1, bf->GetSize() - 1ull);
                assert(items[0] == 16);
            }
            
            {
                std::array<bool, 10> booleans = {true, true, false, false, true, true, false, false, true, false};
                
                tf->PutInStream(&booleans, 0);
                assert(tf->GetSize() == 10ull);
                
                std::array<int, 4> integers = {75,76,77,78};
                tf->PutInStream(&integers, 5ull);
                assert(tf->GetSize() == 13ull);
                
                std::array<std::string, 3> strings = {"josias"s, "cabrera"s, "altamirano"s};
                tf->PutInStream(&strings, tf->GetSize() - 1ull);
                assert(tf->GetSize() == 35ull);
                
                std::string name = "Liliana"s;
                tf->PutInStream(&name, tf->GetSize());
                assert(tf->GetSize() == 42ull);
            }
        }

        //Test exceptions
        void Test6(BinaryFile<int>* bf, TextFile* tf) {
            assert(bf->GetSize() == 16ull);
            assert(tf->GetSize() == 42ull);
            
            { //using nullptr
                try {
                    int* empty = nullptr;
                    bf->Write(empty);
                    assert(false);
                } catch(std::invalid_argument&) {
                    assert(true);
                }
                
                try {
                    std::string* empty = nullptr;
                    tf->PutInStream(empty);
                    assert(false);
                } catch(std::invalid_argument&) {
                    assert(true);
                }
            }
            
            { //using invalid index while writing
                try {
                    int num = 11;
                    bf->Write(&num, 1ull, 17ull);
                    assert(false);
                } catch(std::invalid_argument&) {
                    assert(true);
                }
                
                try {
                    int num = 11;
                    tf->PutInStream(&num, 43ull);
                    assert(false);
                } catch(std::invalid_argument&) {
                    assert(true);
                }
            }
            
            { //using invalid index while reading
                try {
                    int num;
                    bf->Read(&num, 1ull, 16ull);
                    assert(false);
                } catch(std::invalid_argument&) {
                    assert(true);
                }
                
                try {
                    tf->Substr(1ull, 42ull);
                    assert(false);
                } catch(std::invalid_argument&) {
                    assert(true);
                }
            }
            
            { //using invalid sum of count + index while reading
                try {
                    int num;
                    bf->Read(&num, 16ull, 1ull);
                    assert(false);
                } catch(std::out_of_range&) {
                    assert(true);
                }
                
                try {
                    tf->Substr(42ull, 1ull);
                    assert(false);
                } catch(std::out_of_range&) {
                    assert(true);
                }
            }
        }

        void Test() {
            auto bfile_path = CreatePathObject("out.dat");
            auto tfile_path = CreatePathObject("out.txt");
            
            BinaryFile<int> bfile(bfile_path);
            TextFile tfile(tfile_path);
            
            Test1(&bfile, &tfile);
            Test2(&bfile, &tfile);
            Test3(&bfile, &tfile);
            Test4(&bfile, &tfile);
            Test5(&bfile, &tfile);
            Test6(&bfile, &tfile);
        }
    } //namespace file_handler_testing
} //namespace testing
 */
