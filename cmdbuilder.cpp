#include "cmdbuilder.h"


void CmdBuilder::build(QByteArray data) {
    clear();
    size_ = data.size();
    addHeader();
    addBody(data);
    addCRC();
}

void CmdBuilder::addHeader() {

}

void CmdBuilder::addBody(QByteArray data) {

}

void CmdBuilder::addCRC() {

}

QByteArray* CmdBuilder::read() {
    return &cmd;
}

void CmdBuilder::clear() {
    size_ = 0;
    cmd.clear();
}

void CmdBuilder::send() {

}
