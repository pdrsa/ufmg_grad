<template>
  <v-dialog
    transition="dialog-bottom-transition"
    width="auto"
    height="auto"
  >
    <template v-slot:activator="{ on, attrs }">
      <v-btn
        class="group-name-buttons"
        color="blue"
        text
        outlined
        flatten
        v-bind="attrs"
        v-on="on"
      >
        <h3>Ver Eventos</h3>
      </v-btn>
    </template>
    <template v-slot:default="dialog">
      <v-card
        width="670px"
        height="600px"
      >
        <v-row>
          <v-col>
            <h2 class="ma-5"> Eventos do Grupo </h2>
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
          <v-sheet
            class="ma-auto"
            outlined
            rounded
            elevation="3"
          >
            <v-responsive
              class="overflow-y-auto"
              width="600px"
              height="400px"
            >
              <v-row
                v-for="(event) in events" :key="events.findIndex(x=>x==event)"
              >
                <v-card
                  class="pa-6"
                  height="auto"
                  width="600px"
                >
                  <v-row>
                    <v-row>
                      <v-col>
                      <b class="event-name"> {{ event.event_name }} </b>
                      </v-col>
                      <v-col>
                      <p> {{ event.date }} </p>
                      </v-col>
                    </v-row>
                    <v-row>
                      <p class="event-about"> {{ event.about }} </p>
                    </v-row>
                  </v-row>
                </v-card>
              </v-row>
            </v-responsive>
          </v-sheet>
        </v-row>

        <v-row>
          <v-spacer/>
          <GroupCreateEvents/>
          <v-spacer/>
        </v-row>

      </v-card>
    </template>
  </v-dialog>
</template>
<script>
import GroupCreateEvents from "@/components/GroupCreateEventsComponent";
export default {
  components: {
    GroupCreateEvents
  },
  data: () => ({
    events: [
      {
        event_name: "banana",
        about: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis. Id nibh tortor id aliquet. Proin libero nunc consequat interdum varius sit. Egestas erat imperdiet sed euismod nisi porta lorem mollis aliquam.",
        date: "24/12/2006 16:36"
      },
      {
        event_name: "laranja",
        about: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis. Id nibh tortor id aliquet. Proin libero nunc consequat interdum varius sit. Egestas erat imperdiet sed euismod nisi porta lorem mollis aliquam.",
        date: "24/12/2006 15:36"
      },
      {
        event_name: "kiwi",
        about: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis. Id nibh tortor id aliquet. Proin libero nunc consequat interdum varius sit. Egestas erat imperdiet sed euismod nisi porta lorem mollis aliquam.",
        date: "24/12/2006 14:36"
      },
      {
        event_name: "uva",
        about: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis.",
        date: "24/12/2006 13:36"
      },
      {
        event_name: "pidamonha",
        about: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis. Id nibh tortor id aliquet. Proin libero nunc consequat interdum varius sit. Egestas erat imperdiet sed euismod nisi porta lorem mollis aliquam.",
        date: "24/12/2006 12:36"
      },
      {
        event_name: "coreto",
        about: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Felis bibendum ut tristique et egestas quis. Habitasse platea dictumst quisque sagittis. Id nibh tortor id aliquet. Proin libero nunc consequat interdum varius sit. Egestas erat imperdiet sed euismod nisi porta lorem mollis aliquam.",
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
.event-name {
  padding-top: 46px;
  padding-bottom: 16px;
  padding-left: 16px;
  padding-right: 16px;
}

.event-about {
  padding-top: 2px;
  padding-bottom: 8px;
  padding-left: 28px;
  padding-right: 8px;
}
</style>
