#ifndef __MODEL_H__
#define __MODEL_H__

#include <QString>
#include <string>
#include "database_wrapper.h"
#include "tree_t.h"
#include <iostream>
#include <QObject>


using std::string;

class model_t : public QObject {
    Q_OBJECT
  public:
    model_t(QObject *parent = nullptr);
    void init(const string& database_name, QStringList names);
    void set_names(QStringList args);
    void add_tree();
    string serialize() const;
    void rulealize(std::ostream& text_out, std::ostream& inner_out, std::ostream& xml_out);
signals:
    void tableInitiated();
private:
    database_wrapper_t dbw;
    vector<tree_t*> trees;
    knowledge_base_t kb;
};

#endif
