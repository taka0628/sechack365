#include "../include/test.hpp"

using namespace std;

TEST(deviceTest, usbList)
{
	device_c usb;
	vector<string> usb_list;
	usb_list = usb.get_usbList();
	ASSERT_FALSE(usb_list.empty());
	cout << "usblist" << endl;
	for (string usb : usb_list)
	{
		cout << usb << endl;
	}
}