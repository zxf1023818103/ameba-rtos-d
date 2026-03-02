#include <FreeRTOS.h>
#include <task.h>
#include <platform_stdlib.h>
#include <httpc/httpc.h>

#define USE_HTTPS    1
#define SERVER_HOST  "www.baidu.com"

static void example_httpc_thread(void *param)
{
	/* To avoid gcc warnings */
	( void ) param;
	
	struct httpc_conn *conn = NULL;

	// Delay to wait for IP by DHCP
	vTaskDelay(10000);
	printf("\nExample: HTTPC\n");

	/* test GET to https://www.baidu.com/ */
#if USE_HTTPS
	conn = httpc_conn_new(HTTPC_SECURE_TLS, NULL, NULL, NULL);
#else
	conn = httpc_conn_new(HTTPC_SECURE_NONE, NULL, NULL, NULL);
#endif
	if(conn) {
#if USE_HTTPS
		if(httpc_conn_connect(conn, SERVER_HOST, 443, 0) == 0) {
#else
		if(httpc_conn_connect(conn, SERVER_HOST, 80, 0) == 0) {
#endif
			printf("\nConnected to %s\n", SERVER_HOST);
			/* HTTP GET request */
			// start a header and add Host (added automatically), Content-Type and Content-Length (added by input param)
			httpc_request_write_header_start(conn, "GET", "/", NULL, 0);
			printf("\nHTTP GET request header sent\n");
			// add other required header fields if necessary
			httpc_request_write_header(conn, "Connection", "close");
			printf("\nHTTP GET request header finished\n");
			// finish and send header
			httpc_request_write_header_finish(conn);
			printf("\nHTTP GET request sent\n");

			// receive response header
			if(httpc_response_read_header(conn) == 0) {
				httpc_conn_dump_header(conn);

				// receive response body
				if(httpc_response_is_status(conn, "200 OK")) {
					uint8_t buf[1024];
					int read_size = 0; 
					uint32_t total_size = 0;

					while(1) {
						memset(buf, 0, sizeof(buf));
						read_size = httpc_response_read_data(conn, buf, sizeof(buf) - 1);

						if(read_size > 0) {
							total_size += read_size;
							printf("%s", buf);
						}
						else {
							break;
						}

                        char chunk[] = "chunked";
                        /* chunked read */
                        if((conn->response.trans_enc) && (memcmp(conn->response.trans_enc, chunk, strlen(chunk)) == 0)){
                            if(0 == conn->response.trans_chunk_len){
                                break;
                            }
                        }
                        else{
    						if(conn->response.content_len && (total_size >= conn->response.content_len))
    							break;
                        }
					}
				}
			}
		}
		else {
			printf("\nERROR: httpc_conn_connect\n");
		}

		httpc_conn_close(conn);
		httpc_conn_free(conn);
	}

	vTaskDelete(NULL);
}

void example_httpc(void)
{
	if(xTaskCreate(example_httpc_thread, ((const char*)"example_httpc_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_httpc_thread) failed", __FUNCTION__);
}
