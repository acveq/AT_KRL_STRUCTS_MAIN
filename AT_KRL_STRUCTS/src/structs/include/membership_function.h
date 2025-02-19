#ifndef MEMBERSHIP_FUNCTION_H
#define MEMBERSHIP_FUNCTION_H

#include <string>
#include <vector>
#include <libxml/tree.h>
#include <json/json.h>
#include "kb_entity.h"

using namespace std;

// Класс MFPoint
class MFPoint : public KBEntity {
public:
    double x;
    double y;

    MFPoint(double x, double y);

    map<string, string> getAttrs() const override;
    string KRL() const override;
    Json::Value toJSON() const override;

    static MFPoint* fromXML(const xmlNodePtr xml);
    static MFPoint* fromJSON(const Json::Value& json);
};

// Класс MembershipFunction
class MembershipFunction : public KBEntity {
public:
    string name;
    double min;
    double max;
    vector<MFPoint*> points;

    MembershipFunction(const string& name, double min, double max, const vector<MFPoint*>& points);

    map<string, string> getAttrs() const override;
    vector<xmlNodePtr> getInnerXML() const override;
    Json::Value toJSON() const override;

    static MembershipFunction* fromXML(const xmlNodePtr xml);
    static MembershipFunction* fromJSON(const Json::Value& json);

    string KRL() const override;
};

#endif // MEMBERSHIP_FUNCTION_H
