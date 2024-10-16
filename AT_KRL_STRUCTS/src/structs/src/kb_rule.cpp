#include "kb_rule.h"
#include "kb_entity.h"

KBRule::KBRule(const string id, const string tag, const char* desc) : KBEntity(tag), id(id) {

}
KBRule::~KBRule(){

}
void KBRule::init(){}
void KBRule::attrs(){}
void KBRule::innerXml(){}
void KBRule::fromXml(){}
void KBRule::dict(){}
