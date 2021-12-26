//
// Created by UlianaBespalova on 10.11.2021.
//
#include <fstream>

#include "bitopManager.h"
#include "serializers.h"

GroupParams parseGroup(const std::string &group) {
    std::string faculty;
    std::string department;
    for (auto symbol : group) {
        if (symbol == '-') break;
        if (symbol > '9' || symbol < '0') faculty += symbol;
        department += symbol;
    }
    return {faculty, department, group};
}

ResponseString getBadScheduleRequest() {
    const std::string BAD_REQUEST_MSG = R"({ "error": "bad params" })";

    ResponseString response;
    response.body() = BAD_REQUEST_MSG;
    response.set(boost::beast::http::field::content_type, "application/json");
    response.result(boost::beast::http::status::bad_request);
    return response;
}

BitopManager::BitopManager() : headers({{tokenHeader, token}}) {}

ResponseString BitopManager::getSchedule_test() {
    GroupParams groupParams = parseGroup("ИУ5-12М");
    std::string schedule = getScheduleForGroup(groupParams);

    ResponseString response;
    response.body() = schedule;
    response.set(boost::beast::http::field::content_type, "application/json");
    response.result(boost::beast::http::status::ok);
    return response;
}

ResponseString BitopManager::getSchedule(Request request) {
    std::string group = ScheduleRequest(request).group;
    if (group.empty()) return getBadScheduleRequest();

    GroupParams groupParams = parseGroup(group);
    if (groupParams.faculty.empty() || groupParams.department.empty() ||
        groupParams.group.empty()) {
        return getBadScheduleRequest();
    }
    std::string schedule = getScheduleForGroup(groupParams);

    ResponseString response;
    response.body() = schedule;
    response.set(boost::beast::http::field::content_type, "application/json");
    response.result(boost::beast::http::status::ok);
    return response;
}

std::string BitopManager::getScheduleForGroup(const GroupParams &groupParams) {
    std::string facultyUuid =
            cacheManager->getFacultyCache().itemList[groupParams.faculty];
    if (facultyUuid.empty()) return "";

    std::string departments = getItemsByUuid(facultyUuid, "department");
    if (departments.empty()) return "";
    ScheduleListResponse departmentsMap = ScheduleListResponse(departments);
    std::string departmentUuid = departmentsMap.itemList[groupParams.department];
    if (departmentUuid.empty()) return "";

    std::string groups = getItemsByUuid(departmentUuid, "group");
    if (groups.empty()) return "";
    ScheduleListResponse groupsMap = ScheduleListResponse(groups);
    std::string groupUuid = groupsMap.itemList[groupParams.group];
    if (groupUuid.empty()) return "";

    std::string schedule = getScheduleByGroupUuid(groupUuid);
    return schedule;
}

std::string BitopManager::getItemsByUuid(const std::string &uid,
                                         const std::string &type) {
    Params body = {{"parent_uuid", uid}, {"query", ""}, {"type", type}};
    client = new HttpsClient();
    Response result =
            client->makePostRequest(HostAddress(bitopDomain, bitopIP, bitopPort),
                                    scheduleListTarget, nullptr, &headers, &body);
    ResponseStruct resultStruct = client->parseResponse(result);
    delete client;
    if (resultStruct.status == 200)
        return resultStruct.body;
    else
        return "";
}

std::string BitopManager::getScheduleByGroupUuid(const std::string &uid) {
    client = new HttpsClient();
    Response result =
            client->makeGetRequest(HostAddress(bitopDomain, bitopIP, bitopPort),
                                   scheduleTarget + uid, nullptr, &headers);
    ResponseStruct resultStruct = client->parseResponse(result);
    std::cout << resultStruct.body << std::endl;

    delete client;
    if (resultStruct.status == 200)
        return resultStruct.body;
    else
        return "";
}
