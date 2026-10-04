#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define MAX_DATA 512
#define MAX_ROWS 100


struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

struct Database {
	struct Address rows[MAX_ROWS];
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void die(const char *message) {

	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

 41

 42    void Database_load(struct Connection *conn)

 43    {

 44        int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);

 45        if (rc != 1)

 46            die("Failed to load database.");

 47    }

 48

 49    struct Connection *Database_open(const char *filename, char mode)

 50    {

 51        struct Connection *conn = malloc(sizeof(struct Connection));

 52        if (!conn)

 53            die("Memory error");

 54

 55        conn->db = malloc(sizeof(struct Database));

 56        if (!conn->db)

 57            die("Memory error");

 58

 59        if (mode == 'c') {

 60            conn->file = fopen(filename, "w");

 61        } else {

 62            conn->file = fopen(filename, "r+");

 63

 64            if (conn->file) {

 65                Database_load(conn);

 66            }

 67        }

 68

 69        if (!conn->file)

 70            die("Failed to open the file");

 71

 72        return conn;

 73    }

 74

 75    void Database_close(struct Connection *conn)

 76    {

 77        if (conn) {

 78            if (conn->file)

 79                fclose(conn->file);

 80            if (conn->db)

 81                free(conn->db);

 82            free(conn);

 83        }

 84    }

 85

 86    void Database_write(struct Connection *conn)

 87    {

 88        rewind(conn->file);

 89

 90        int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);

 91        if (rc != 1)

 92            die("Failed to write database.");

 93

 94        rc = fflush(conn->file);

 95        if (rc == -1)

 96            die("Cannot flush database.");

 97    }

 98

 99    void Database_create(struct Connection *conn)

100    {

101        int i = 0;

102

103        for (i = 0; i < MAX_ROWS; i++) {

104            // make a prototype to initialize it

105            struct Address addr = {.id = i,.set = 0 };

106            // then just assign it

107            conn->db->rows[i] = addr;

108        }

109    }

110

111    void Database_set(struct Connection *conn, int id, const char *name,

112            const char *email)

113    {

114        struct Address *addr = &conn->db->rows[id];

115        if (addr->set)

116            die("Already set, delete it first");

117

118        addr->set = 1;

119        // WARNING: bug, read the "How To Break It" and fix this

120        char *res = strncpy(addr->name, name, MAX_DATA);

121        // demonstrate the strncpy bug

122        if (!res)

123            die("Name copy failed");

124

125        res = strncpy(addr->email, email, MAX_DATA);

126        if (!res)

127            die("Email copy failed");

128    }

129

130    void Database_get(struct Connection *conn, int id)

131    {

132        struct Address *addr = &conn->db->rows[id];

133

134        if (addr->set) {

135            Address_print(addr);

136        } else {

137            die("ID is not set");

138        }

139    }

140

141    void Database_delete(struct Connection *conn, int id)

142    {

143        struct Address addr = {.id = id,.set = 0 };

144        conn->db->rows[id] = addr;

145    }

146

147    void Database_list(struct Connection *conn)

148    {

149        int i = 0;

150        struct Database *db = conn->db;

151

152        for (i = 0; i < MAX_ROWS; i++) {

153            struct Address *cur = &db->rows[i];

154

155            if (cur->set) {

156                Address_print(cur);

157            }

158        }

159    }

160

161    int main(int argc, char *argv[])

162    {

163        if (argc < 3)

164            die("USAGE: ex17 <dbfile> <action> [action params]");

165

166        char *filename = argv[1];

167        char action = argv[2][0];

168        struct Connection *conn = Database_open(filename, action);

169        int id = 0;

170

171        if (argc > 3) id = atoi(argv[3]);

172        if (id >= MAX_ROWS) die("There's not that many records.");

173

174        switch (action) {

175            case 'c':

176                Database_create(conn);

177                Database_write(conn);

178                break;

179

180            case 'g':

181                if (argc != 4)

182                    die("Need an id to get");

183

184                Database_get(conn, id);

185                break;

186

187            case 's':

188                if (argc != 6)

189                    die("Need id, name, email to set");

190

191                Database_set(conn, id, argv[4], argv[5]);

192                Database_write(conn);

193                break;

194

195            case 'd':

196                if (argc != 4)

197                    die("Need id to delete");

198

199                Database_delete(conn, id);

200                Database_write(conn);

201                break;

202

203            case 'l':

204                Database_list(conn);

205                break;

206            default:

207                die("Invalid action: c=create, g=get, s=set, d=del, l=list");

208        }

209

210        Database_close(conn);

211

212        return 0;

213    }

