#include <iostream>
#include<sstream>
#include<fstream>
using namespace std;


struct Frame_Header {
	uint16_t total_data_length = 0;
};
struct Basic_Information {
	uint16_t module_data_length = 0;
	bool data_status = 0;
	uint16_t year = 0;
	uint16_t mounth = 0;
	uint16_t day = 0;;
	uint16_t hours = 0;;
	uint16_t minutes = 0;;
	uint16_t seconds = 0;;
	uint16_t miliseconds = 0;;
	uint16_t total_number_of_targets = 0;;
	uint16_t information_for_each_target = 0;;
	uint16_t total_number_of_lanes = 0;;
	uint16_t information_for_each_lane = 0;
	uint16_t flow_information_output = 0;
	uint16_t traffic_per_lane = 0;
	uint16_t traffic_data_reporting_interval = 0;
	uint16_t general_traffic_conditions = 0;
	uint16_t event_alarm = 0;
	uint16_t protocol_version = 0;
	uint16_t module_verification = 0;
	uint16_t unknown_data = 0;
};
struct Target_Message {
	uint16_t module_data_length = 0;
	uint16_t the_Nth_goal_numbering = 0;
	unsigned int vertical_distance = 0;
	unsigned int lateral_distance = 0;
	unsigned int speed_y_direction = 0;
	uint16_t target_type = 0;
	uint16_t lane_number = 0;
	unsigned int front_spacing = 0;
	unsigned int front_time_interval = 0;
	unsigned int speed_x_direction = 0;
	uint16_t heading_angle = 0;
	uint16_t incidents = 0;
	unsigned int radar_network_X = 0;
	unsigned int radar_network_Y = 0;
	uint16_t fill_the_blind_mark = 0;
	unsigned int car_length = 0;
	unsigned int car_width = 0;
	uint16_t module_verification = 0;
	uint16_t unknown_data = 0;
};
struct Road_Info {
	uint16_t module_data_length = 0;
	uint16_t lane = 0;
	uint16_t lane_Line_up_Length = 0;
	uint16_t lane_Congestion_Degree = 0;
	uint16_t module_verification = 0;

};
//Hex parser from txt file buffer 
stringstream Parse_hex(fstream& fs, size_t length) {
	string str;
	string sum;
	for (size_t it = 0; it < length; ++it) {
		getline(fs, str);
		sum += str;
		sum += '\n';
	}
	auto it = find(next(sum.rbegin(), 1), sum.rend(), '\n');
	stringstream result;
	if (it != sum.rend()) {
		result << *(next(it, 2));
		result << *(next(it, 1));
	}
	result << sum[sum.size() - 3];
	result << sum[sum.size() - 2];
	return result;
}

void FrameHeader(fstream& fs, Frame_Header& fh) {
	Parse_hex(fs, 2) >> hex >> fh.total_data_length;
};
void BasicInformation(fstream& fs, Basic_Information& bi) {
	Parse_hex(fs, 2) >> hex >> bi.module_data_length;
	Parse_hex(fs, 1) >> hex >> bi.data_status;
	Parse_hex(fs, 1) >> hex >> bi.year;
	Parse_hex(fs, 1) >> hex >> bi.mounth;
	Parse_hex(fs, 1) >> hex >> bi.day;
	Parse_hex(fs, 1) >> hex >> bi.hours;
	Parse_hex(fs, 1) >> hex >> bi.minutes;
	Parse_hex(fs, 1) >> hex >> bi.seconds;
	Parse_hex(fs, 1) >> hex >> bi.miliseconds;
	Parse_hex(fs, 1) >> hex >> bi.total_number_of_targets;
	Parse_hex(fs, 1) >> hex >> bi.information_for_each_target;
	Parse_hex(fs, 1) >> hex >> bi.total_number_of_lanes;
	Parse_hex(fs, 1) >> hex >> bi.information_for_each_lane;
	Parse_hex(fs, 1) >> hex >> bi.flow_information_output;
	Parse_hex(fs, 1) >> hex >> bi.traffic_per_lane;
	Parse_hex(fs, 2) >> hex >> bi.traffic_data_reporting_interval;
	Parse_hex(fs, 1) >> hex >> bi.general_traffic_conditions;
	Parse_hex(fs, 1) >> hex >> bi.event_alarm;
	Parse_hex(fs, 2) >> hex >> bi.protocol_version;
	Parse_hex(fs, 1) >> hex >> bi.module_verification;
	Parse_hex(fs, 2) >> hex >> bi.unknown_data;
};
void TargetMessage(fstream& fs, Target_Message& tm) {
	Parse_hex(fs, 1) >> hex >> tm.the_Nth_goal_numbering;
	Parse_hex(fs, 2) >> hex >> tm.vertical_distance;
	Parse_hex(fs, 2) >> hex >> tm.lateral_distance;
	Parse_hex(fs, 2) >> hex >> tm.speed_y_direction;
	Parse_hex(fs, 1) >> hex >> tm.target_type;
	Parse_hex(fs, 1) >> hex >> tm.lane_number;
	Parse_hex(fs, 2) >> hex >> tm.front_spacing;
	Parse_hex(fs, 2) >> hex >> tm.front_time_interval;
	Parse_hex(fs, 2) >> hex >> tm.speed_x_direction;
	Parse_hex(fs, 2) >> hex >> tm.heading_angle;
	Parse_hex(fs, 1) >> hex >> tm.incidents;
	Parse_hex(fs, 4) >> hex >> tm.radar_network_X;
	Parse_hex(fs, 4) >> hex >> tm.radar_network_Y;
	Parse_hex(fs, 1) >> hex >> tm.fill_the_blind_mark;
	Parse_hex(fs, 1) >> hex >> tm.car_length;
	Parse_hex(fs, 1) >> hex >> tm.car_width;
};
void RoadInfo(fstream& fs, Road_Info& rf) {
	Parse_hex(fs, 1) >> hex >> rf.lane;
	Parse_hex(fs, 2) >> hex >> rf.lane_Line_up_Length;
	Parse_hex(fs, 1) >> hex >> rf.lane_Congestion_Degree;
};




int main()
{
	fstream fs("buffer.txt");
	ofstream of("output.txt");
	if (fs.good() && of.good()) {
		cout << "Start parse..." << '\n';
		while (!fs.eof()) {
			string result;
			Parse_hex(fs, 2) >> result;

			//Checking hex name of fields and send result parsing to file output.txt
			if (result == "ABCD") {
				Frame_Header fh;
				FrameHeader(fs, fh);
				of << "Header module:" << '\n';
				of << "Total data length: " << fh.total_data_length << '\n';
				of << "===================================================" << '\n';
			}
			if (result == "4A42") {
				Basic_Information bi;
				BasicInformation(fs, bi);
				of << "Basic information module." << '\n';
				of << "Module data length: " << bi.module_data_length << '\n';
				of << "Data status: " << bi.data_status << '\n';
				of << "Time: " << '\n';
				of << "-Year(20xx): " << bi.year << '\n';
				of << "-Mounth: " << bi.mounth << '\n';
				of << "-Day: " << bi.day << '\n';
				of << "-Hours: " << bi.hours << '\n';
				of << "-Minutes: " << bi.minutes << '\n';
				of << "-Seconds: " << bi.seconds << '\n';
				of << "-Miliseconds: " << bi.miliseconds << '\n';
				of << "Total number of targets: " << bi.total_number_of_targets << '\n';
				of << "Information for each target, Number of bytes: " << bi.information_for_each_target << '\n';
				of << "Total number of lanes: " << bi.total_number_of_lanes << '\n';
				of << "Information for each lane, Number of bytes: " << bi.information_for_each_lane << '\n';
				of << "Flow information output, Logo: " << bi.flow_information_output << '\n';
				of << "Traffic per lane, Number of bytes of information: " << bi.traffic_per_lane << '\n';
				of << "Traffic data reporting Interval: " << bi.traffic_data_reporting_interval << '\n';
				of << "General Traffic conditions Instructions: " << bi.general_traffic_conditions << '\n';
				of << "Event Alarm: " << bi.event_alarm << '\n';
				of << "Protocol version: " << bi.protocol_version << '\n';
				of << "Module verification: " << bi.module_verification << '\n';
				of << "Unknown data: " << bi.unknown_data << '\n';
				of << "===================================================" << '\n';
			}
			if (result == "4D42") {
				size_t i;
				Parse_hex(fs, 2) >> hex >> i;
				of << "Target message module." << '\n';
				of << "Module data length: " << i << '\n';

				//i-data length, 5 is size module data length + module verification, 29 is size one data block 
				for (size_t n = 1; n <= (i - 5) / 29; ++n) {
					Target_Message tm;
					tm.module_data_length = i;
					TargetMessage(fs, tm);
					of << "The " << n << "th goal numbering: " << tm.the_Nth_goal_numbering << '\n';
					of << "Vertical distance: " << (tm.vertical_distance * 0.1) << "m" << '\n';
					of << "Lateral distance: " << (tm.lateral_distance * 0.1) << "m" << '\n';
					of << "Speed (y direction): " << (tm.speed_y_direction * 0.1) << "m" << '\n';
					of << "Target Type: " << tm.target_type << '\n';
					of << "Lane Number: " << tm.lane_number << '\n';
					of << "Front spacing: " << (tm.front_spacing * 0.1) << "m" << '\n';
					of << "Front time interval: " << (tm.front_time_interval * 0.1) << "m" << '\n';
					of << "Speed (x direction): " << (tm.speed_x_direction * 0.1) << "m" << '\n';
					of << "Heading angle: " << tm.heading_angle % 360 << '\n';
					of << "Incidents: ";
					switch (tm.incidents)
					{
					case(0):
						of << "No event occurred" << '\n';
						break;
					case(1):
						of << "Unblocked parking" << '\n';
						break;
					case(2):
						of << "Congested Parking" << '\n';
						break;
					case(3):
						of << "Vehicle Overspeed" << '\n';
						break;
					case(4):
						of << "Harbour Parking" << '\n';
						break;
					case(5):
						of << "Slow Moving vehicles" << '\n';
						break;
					case(6):
						of << "Pedestrian" << '\n';
						break;
					case(7):
						of << "Retrograde Vehicle" << '\n';
						break;
					case(8):
						of << "Change of direction" << '\n';
						break;
					default:
						break;
					}

					of << "Radar Network X-sit Standard: " << (tm.radar_network_X * 0.1) << "m" << '\n';
					of << "Radar Network Y-sit: " << (tm.radar_network_Y * 0.1) << "m" << '\n';
					of << "Fill the blind mark: " << tm.fill_the_blind_mark << '\n';
					of << "Car length: " << (tm.car_length * 0.1) << "m" << '\n';
					of << "Car width: " << (tm.car_width * 0.1) << "m" << '\n';
					of << "===" << '\n';
				}
				uint16_t mod_ver = 0;
				Parse_hex(fs, 1) >> hex >> mod_ver;
				of << "Module verification: " << mod_ver << '\n';
				of << "===================================================" << '\n';
			}
			if (result == "444C") {
				size_t length = 0;
				Parse_hex(fs, 2) >> hex >> length;
				of << "Module Road info." << '\n';
				of << "Module data length: " << length << '\n';

				//length-size module data
				for (size_t i = 1; i <= (length - 2) / 4; ++i) {
					Road_Info rf;
					RoadInfo(fs, rf);
					of << "Lane " << i << ": " << rf.lane << '\n';
					of << "Line up: " << (rf.lane_Line_up_Length * 0.1) << '\n';
					of << "Congestion: ";
					switch (rf.lane_Congestion_Degree)
					{
					case(0):
						of << "queue not happened" << '\n';
						break;
					case(1):
						of << "soft" << '\n';
						break;
					case(2):
						of << "normal" << '\n';
						break;
					case(3):
						of << "hard" << '\n';
						break;
					case(4):
						of << "queue overflow" << '\n';
						break;
					default:
						of << "Wrong value" << '\n';
						break;
					}


					of << "===" << '\n';
				}
				uint16_t mod_ver = 0;
				Parse_hex(fs, 1) >> hex >> mod_ver;
				of << "Module verification: " << mod_ver << '\n';

			}

		}

	}
	cout << "Parsing is done!";
}
