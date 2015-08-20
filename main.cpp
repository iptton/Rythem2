
#include <rythemapp.h>

int main(int argc, char *argv[]){
    RythemApp rythem(argc, argv);
    if(rythem.isRunning()){
        return 0;
    }
    return rythem.exec();
}
