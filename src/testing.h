
void test()
{
//#ifdef _WIN32
//    SYSTEM_INFO  sys_info;
//    DWORD   err;
//#endif
    unsigned char  buf[120];
    int  i;
    char filename[1000];
    
    fsp_file_stream fs;
    int rb = 0;
    fsp_automation aut;
    fsp_cmd_args cmd_args;

    int const data_size = 10;
    fsp_shift_buffer sh_buf;
    char data[10];

    //mf = fsp_map_file("input", size, 0, 0);
    //err = GetLastError();
    //buf = (char*)mf.region;
    //for (i = 0; i < mf.size; ++i)
    //    printf("%c", buf[i]);
    //fsp_unmap_file(&mf);
    //GetSystemInfo(&sys_info);

    //if (!fsp_parse(argc, argv, &cmd_args))
    //{
    //    printf("Arguments parse error\n");
    //    return 1;
    //}

    //fs = fsp_open_file("input", om_read);
    //if (fsp_bad(&fs))
    //{
    //    printf("Can't open file specified: 'input'\n");
    //    return 1;
    //}

    //while ((rb = fsp_read(&fs, buf, 15)) > 0)
    //{
    //    for (i = 0; i < rb; ++i)
    //        printf("%d ", (int)buf[i]);
    //}

    //fsp_gen_name(filename, 1000, "AllYourBase", 1);


    if (fsp_automation_init(&aut, "xyz", 3))
    {
        //printf("\n%d\n", fsp_automation_find_in(&aut, "abcdefghijklmnopqrstuvwx", sizeof("abcdefghijklmnopqrstuvwx") - 1));
        //printf("\n%d\n", fsp_automation_find_in(&aut, "yzzzyx", sizeof("yzzzyx") - 1));
        fsp_automation_free(&aut);
    }

    for (i = 0; i < data_size; ++i)
    {
        data[i] = (char)i;
    }
    fsp_sbuf_init(&sh_buf, data_size);
    fsp_sbuf_push(&sh_buf, data, data_size);
    for (i = 0; i < data_size; ++i)
    {
        printf("%d\n", sh_buf.data[i]);
    }

    for (i = 0; i < data_size / 2; ++i)
    {
        data[i] = (char)(10 + i);
    }
    fsp_sbuf_push(&sh_buf, data, data_size / 2);
    for (i = 0; i < data_size; ++i)
    {
        printf("%d\n", sh_buf.data[i]);
    }

    for (i = 0; i < data_size / 2; ++i)
    {
        data[i] = (char)(20 + i);
    }
    fsp_sbuf_push(&sh_buf, data, data_size / 2);
    for (i = 0; i < data_size; ++i)
    {
        printf("%d\n", sh_buf.data[i]);
    }

    fsp_sbuf_free(&sh_buf);
}