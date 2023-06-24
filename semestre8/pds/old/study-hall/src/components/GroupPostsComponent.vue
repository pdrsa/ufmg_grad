<template>
  <v-container>
    <v-card
      rounded="xl"
      color="#FFFFFF"
      elevation="10"
      max-width="800px"
      height="600px"
      class="bigrect-group-posts"
    >

      <v-row>
        <h1 class="pa-8"> Posts </h1>
        <v-spacer></v-spacer>
      </v-row>

      <v-row>
        <v-sheet
          class="ma-5"
          outlined
          rounded
        >
          <v-responsive
            class="overflow-y-auto"
            max-height="380px"
          >
            <v-row
              v-for="(post) in posts" :key="posts.findIndex(x=>x==post)"
            >
              <v-card
                class="pa-6"
                height="auto"
                width="800px"
              >
                <v-row>
                  <v-col cols="2">
                    <v-img :src="user_avatar"
                    height="90px"
                    width="90px"
                    class="ma-4"
                    ></v-img>
                  </v-col>
                  <v-col>
                    <v-row>
                      <p class="date-post"> {{ post.date }} </p>
                    </v-row>
                    <v-row>
                      <p class="content-post"> {{ post.content }} </p>
                    </v-row>
                  </v-col>
                </v-row>
              </v-card>
            </v-row>
          </v-responsive>
        </v-sheet>
      </v-row>

      <v-row>
        <v-spacer></v-spacer>
        <v-dialog
          transition="dialog-bottom-transition"
          width="auto"
          height="auto"
        >
          <template v-slot:activator="{ on, attrs }">
            <v-btn 
              class="ma-3"
              color="blue"
              v-bind="attrs"
              v-on="on"
            >
              <h3> Criar Post </h3>
            </v-btn>
          </template>
          <template v-slot:default="dialog">
            <v-card
              width="570px"
              height="400px"
            >
              <v-row>
                <v-col>
                  <h2 class="ma-5"> Criar Post </h2>
                </v-col>
                <v-col>
                  <v-card-actions class="justify-end">
                    <v-btn
                      class="ma-3"
                      color="blue"
                      @click="dialog.value = false"
                    >Fechar</v-btn>
                  </v-card-actions>
                </v-col>
              </v-row>

              <v-row>
                <v-textarea
                clearable
                label="Escreva aqui"
                v-model="postcontent"
                height="120px"
                class="ma-8"
                ></v-textarea>
              </v-row>
              <v-row>
                <v-spacer/>
                <v-btn
                  class="ma-1"
                  color="blue"
                  @click="post();dialog.value=false"
                >
                  <h3> Postar </h3>
                </v-btn>
                <v-spacer/>
              </v-row>
            </v-card>
          </template>
        </v-dialog>
        <v-spacer></v-spacer>
      </v-row>

    </v-card>
  </v-container>
</template>
<script>
export default {
  data: () => ({
    user_avatar: "https://cdn.icon-icons.com/icons2/1378/PNG/512/avatardefault_92824.png",
    posts: [
      {
        username: "banana",
        content: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis. Id nibh tortor id aliquet. Proin libero nunc consequat interdum varius sit. Egestas erat imperdiet sed euismod nisi porta lorem mollis aliquam.",
        date: "24/12/2006 16:36"
      },
      {
        username: "laranja",
        content: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis. Id nibh tortor id aliquet. Proin libero nunc consequat interdum varius sit. Egestas erat imperdiet sed euismod nisi porta lorem mollis aliquam.",
        date: "24/12/2006 15:36"
      },
      {
        username: "kiwi",
        content: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis. Id nibh tortor id aliquet. Proin libero nunc consequat interdum varius sit. Egestas erat imperdiet sed euismod nisi porta lorem mollis aliquam.",
        date: "24/12/2006 14:36"
      },
      {
        username: "uva",
        content: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis.",
        date: "24/12/2006 13:36"
      },
      {
        username: "pidamonha",
        content: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis. Id nibh tortor id aliquet. Proin libero nunc consequat interdum varius sit. Egestas erat imperdiet sed euismod nisi porta lorem mollis aliquam.",
        date: "24/12/2006 12:36"
      },
      {
        username: "coreto",
        content: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis. Id nibh tortor id aliquet. Proin libero nunc consequat interdum varius sit. Egestas erat imperdiet sed euismod nisi porta lorem mollis aliquam.",
        date: "24/12/2006 11:36"
      }
    ]
  }),
  methods: {
    post () {
      this.posts.unshift({username:"teste", content:this.postcontent, date: "24/12/2007 15:23"})
      this.postcontent=""
    }
  }
}
</script>
<style>
.bigrect-group-posts {
  margin-top: 30px;
  margin-bottom: 20px;
  margin-left: 170px;
}
.date-post {
  margin-top: 4px;
  margin-bottom: 4px;
  margin-left: 4px;
  margin-right: 4px;
}
.content-post {
  padding-top: 4px;
  padding-bottom: 4px;
  padding-left: 4px;
  padding-right: 4px;
}
</style>
