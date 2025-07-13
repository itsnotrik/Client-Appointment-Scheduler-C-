 Project Title: Client Appointment Scheduler (C++)

 Developed by: Rik Danielle Argarin

 Description

A simple console-based appointment scheduler system written in C++.
This program allows users to book appointments, and admins to manage (view, search, and delete) them. All data is saved in a text file (appointments.txt) so it persists between runs.

It features:

✅ Login System with role-based access
✅ Input validation for date/time
✅ Duplicate appointment slot prevention
✅ File saving/loading
✅ Clean and structured code

🔐 Roles & Access
Role	Username	Password
Admin	admin	admin123
User	user	user123

Features

User
Book new appointment

View all appointments

Search appointments by name


Admin
View all appointments

Search appointments

Delete appointments by ID



💡 Notes
Appointment date must be in YYYY-MM-DD format

Time must be in HH:MM (24-hour format)

The system will reject bookings for duplicate date+time

You can reset the data by deleting appointments.txt
