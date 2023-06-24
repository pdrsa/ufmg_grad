<template>
  <v-dialog
    transition="dialog-bottom-transition"
    width="auto"
    height="auto"
  >
    <template v-slot:activator="{ on, attrs }">
      <v-btn 
        class="mt-8"
        color="blue"
        v-bind="attrs"
        v-on="on"
      >
        <h3> Criar Evento </h3>
      </v-btn>
    </template>
    <template v-slot:default="dialog">
      <v-card
        width="450px"
        height="600px"
      >
        <v-row>
          <v-col>
            <h2 class="ma-5"> Criar Evento </h2>
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
          <v-text-field
          class="ml-12"
          label="Nome do Evento"
          ref="event_name"
          filled
          clearable
          rounded
          >
          </v-text-field>
          <v-spacer/>
        </v-row>

        <v-row>
          <v-text-field
          class="ml-12"
          label="Data do Evento"
          ref="event_date"
          filled
          clearable
          rounded
          >
          </v-text-field>
          <v-spacer/>
        </v-row>

        <v-row>
          <v-textarea
          class="event-about-create"
          label="Informações sobre o evento"
          v-model="event_about"
          height="210px"
          rounded
          clearable
          filled
          ></v-textarea>
          <v-spacer/>
        </v-row>

        <v-row>
          <v-spacer/>
          <v-btn
            class="mt-2"
            color="blue"
            @click="create();dialog.value=false"
          >
            <h3> Criar </h3>
          </v-btn>
          <v-spacer/>
        </v-row>

      </v-card>
    </template>
  </v-dialog>
</template>
<script>
export default {
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
    create () {
      alert("Evento criado")
    }
  }
}
</script>
<style>
.event-about-create {
  width: 270px;
  margin-left: 50px !important;
}
</style>
