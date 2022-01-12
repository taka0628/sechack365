#include "../include/test.hpp"

using namespace std;

constexpr char USB_ID[] = "8564:1000";

TEST(deviceTest, usbList)
{
    device_c usb;
    vector<string> usb_list;
    usb_list = usb.get_usbList();
    ASSERT_FALSE(usb_list.empty());
    // cout << "usblist" << endl;
    for (string usb : usb_list) {
        cout << usb << endl;
    }
}

TEST(deviceTest, setUsbID)
{
    device_c usb;
    ERROR_TEST;
    ASSERT_FALSE(usb.set_usbID("hoge"));
    ASSERT_FALSE(usb.set_usbID(""));
    ASSERT_FALSE(usb.set_usbID("1d6b:000"));
    ASSERT_FALSE(usb.set_usbID("1d6b:0005"));
    TEST_END;

    ASSERT_TRUE(usb.set_usbID("8564:1000"));
    string temp = usb.get_usbID();
    ASSERT_STREQ("8564:1000", temp.c_str());
    temp.clear();
    temp = usb.get_usbSerial();
    ASSERT_STREQ("0937TOHGYQA37A3M", temp.c_str());
}

TEST(deviceTest, UsbidFile)
{
    TestLog_c test("USB IDファイルのテスト");
    device_c usb;
    ASSERT_TRUE(usb.add_usbID2file(USB_ID));
    ASSERT_TRUE(usb.set_usbID_form_file());
    ASSERT_TRUE(usb.is_exist_usbID_in_file(USB_ID));
    ASSERT_TRUE(usb.add_usbID2file("1d6b:0003"));
    ASSERT_TRUE(usb.set_usbID_form_file());
    ASSERT_TRUE(usb.is_exist_usbID_in_file("1d6b:0003"));

    ERROR_TEST;
    device_c error_usb;
    ASSERT_FALSE(error_usb.is_exist_usbID_in_file("1111:1111"));
    ASSERT_FALSE(error_usb.add_usbID2file("1111:1111"));
}