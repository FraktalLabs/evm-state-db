#pragma once

struct RunData;
struct SetValueData;
struct GetValueData;

void runDB(const RunData& data);
void setDBValue(const SetValueData& data);
void getDBValue(const GetValueData& data);

int runDBCmdline(int argc, char* argv[]);
int setDBValueCmdline(int argc, char* argv[]);
int getDBValueCmdline(int argc, char* argv[]);
