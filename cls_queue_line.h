#pragma once
#pragma warning(disable : 4996)

#include <queue>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

class cls_queue_line
{
private:
	string _prefix;

	short _total_tickets = 0, _served_clients = 0, _serving_duration;

	struct _st_client
	{
		string client_code, access_time;
		short client_number;
	};

	queue <_st_client> _queue_line;

	string _get_date()
	{
		short day, month, year, hour, minute, second;
		time_t t = time(0);
		tm* now = localtime(&t);
		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		day = now->tm_mday;
		hour = now->tm_hour;
		minute = now->tm_min;
		second = now->tm_sec;
		return to_string(day) + '/' + to_string(month) + '/' + to_string(year) + " - " + to_string(hour) + ':' + to_string(minute) + ':' + to_string(second);
	}

	void _print(_st_client client)
	{
		cout << "\n\t\t\t  _______________________\n";
		cout << "\n\t\t\t\t    " << client.client_code;
		cout << "\n\n\t\t\t    " << client.access_time;
		cout << "\n\t\t\t    Wating Clients = " << _queue_line.size();
		cout << "\n\t\t\t      Serve Time In";
		cout << "\n\t\t\t       " << _serving_duration * (client.client_number - _served_clients - 1) << " Minutes.";
		cout << "\n\t\t\t  _______________________\n";
	}

public:
	cls_queue_line(string prefix, short serving_duration)
	{
		_prefix = prefix;
		_serving_duration = serving_duration;
	}

	void issue_ticket()
	{
		_total_tickets++;
		_st_client client;
		client.client_number = _total_tickets;
		client.client_code = _prefix + to_string(client.client_number);
		client.access_time = _get_date();
		_queue_line.push(client);
	}

	void print_info()
	{
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t\tQueue Info";
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t    Prefix   = " << _prefix;
		cout << "\n\t\t\t    Total Tickets   = " << _total_tickets;
		cout << "\n\t\t\t    Served Clients  = " << _served_clients;
		cout << "\n\t\t\t    Wating Clients  = " << _queue_line.size();
		cout << "\n\t\t\t _________________________\n\n";
	}

	void print_tickets_line_RTL()
	{
		if (_queue_line.empty()) cout << "\n\t\tTickets: No Tickets.";
		else
		{
			cout << "\n\t\tTickets: ";
			queue <_st_client> temp_queue_line = _queue_line;
			while (!temp_queue_line.empty())
			{
				cout << ' ' << temp_queue_line.front().client_code << " <-- ";
				temp_queue_line.pop();
			}
		}
		cout << endl;
	}

	void print_tickets_line_LTR()
	{
		if (_queue_line.empty()) cout << "\n\t\tTickets: No Tickets.";
		else
		{
			cout << "\n\t\tTickets: ";
			queue <_st_client> temp_queue_line = _queue_line;
			stack <_st_client> temp_stack_line;
			while(!temp_queue_line.empty())
			{
				temp_stack_line.push(temp_queue_line.front());
				temp_queue_line.pop();
			}
			while (!temp_stack_line.empty())
			{
				cout << ' ' << temp_stack_line.top().client_code << " --> ";
				temp_stack_line.pop();
			}
		}
		cout << endl;
	}

	void print_all_tickets()
	{
		if (_queue_line.empty()) cout << "\n\n\t\t\t     ---No Tickets---\n";
		else
		{
			cout << "\n\n\t\t\t       ---Tickets---";
			queue <_st_client> temp_queue_line = _queue_line;
			while (!temp_queue_line.empty())
			{
				_print(temp_queue_line.front());
				temp_queue_line.pop();
			}
		}
	}

	void serve_next_client()
	{
		if (!_queue_line.empty())
		{
			_served_clients++;
			_queue_line.pop();
		}
	}
};