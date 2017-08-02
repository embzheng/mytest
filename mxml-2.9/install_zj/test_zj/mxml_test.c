#include "mxml.h"


void creat_mxml()
{
    FILE *fp;
    
    
    mxml_node_t *xml;
    mxml_node_t *data;
    mxml_node_t *node;
    mxml_node_t *group;
    
    xml = mxmlNewXML("1.0");
    data = mxmlNewElement(xml, "data");
	mxmlNewText(data, 0, "val1");
    node = mxmlNewElement(data, "node");    
    mxmlNewText(node, 0, "val2");
    


    fp = fopen("test.xml", "w+");
    mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);

    fclose(fp);
    mxmlDelete(xml);
}

int find_mxml()
{
    FILE *fp;
    mxml_node_t *tree,*app, *key;
    u_char keynum = 0;
    u_char id = 0;
    int i;

    fp = fopen("test.xml", "r");
    if (fp == NULL) {
        
        return 0;
    }
    tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
    if (tree == NULL) {
        return 0;
    }
    fclose(fp);

    for (app = mxmlFindElement(tree, tree, "appname", "enable", "1", MXML_DESCEND); app != NULL;
        app = mxmlFindElement(app, tree, "appname", "enable", "1", MXML_DESCEND))    { 
        printf(" name:%s \n",mxmlElementGetAttr(app,"name"));
        printf(" id:%s \n",mxmlElementGetAttr(app,"id"));
        printf(" enable:%s \n",mxmlElementGetAttr(app,"enable"));
        printf(" appmatch:%s \n",mxmlElementGetAttr(app,"appmatch"));
        keynum = atoi(mxmlElementGetAttr(app,"keynum"));
        for (key = mxmlFindElement(app, tree, "key", "id", NULL, MXML_DESCEND ); key != NULL;
            key = mxmlFindElement(key, tree, "key", "id", NULL, MXML_DESCEND )) {
            
            id = atoi(mxmlElementGetAttr(key, "id"));
            printf(" id:%d \n",id);
            printf(" keyfind:%s \n",mxmlElementGetAttr(key,"keyfind"));
        }
    }
    mxmlDelete(tree);

    return 0 ;
}


int main(int argc,char *argv[])
{   
    int ret;
    int     i_opt;
    
	//creat_mxml();
    find_mxml();
#if 0    
    while ((i_opt = getopt(argc, argv, "h")) != -1) {
        switch (i_opt) {
            case 'h':
                test_usage();
                break;

            default:
                test_usage();
        }
    }
#endif	
}
