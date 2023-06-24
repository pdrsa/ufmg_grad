<template>
  <v-container>
    <v-card
      rounded="xl"
      color="#FFFFFF"
      elevation="10"
      max-width="800px"
      height="450px"
      class="bigrect-group-name"
    >

      <v-row>
        <v-spacer/>
        <h1 class="ma-10"> {{ group.group_name }} </h1>
        <v-spacer/>
      </v-row>

      <v-row>
        <v-col cols="7">
          <v-img :src="photo_src"
          height="250px"
          width="250px"
          class="group_avatar"
          ></v-img>
        </v-col>
        <v-col>
          <p>Organizador: {{ group.organizer_name }}</p>
          <p>Contato: {{ group.organizer_contact }}</p>
          <v-btn
            class="group-name-buttons"
            color="blue"
            text
            outlined
            flatten
            @click="entrar"
          >
            <h3>Entrar no Grupo</h3>
          </v-btn>

          <GroupEvents/>

          <p class="mt-4">Interesse do Grupo</p>
          <v-item
            v-slot="{ active, toggle }"
          >
            <v-chip
              active-class="yellow--text"
              :input-value="active"
              @click="toggle"
              draggable
            >
            {{ group.interest }}
            </v-chip>
          </v-item>
        </v-col>
      </v-row>

    </v-card>
  </v-container>
</template>
<script>
import GroupEvents from "@/components/GroupEventsComponent";
export default {
  components: {
    GroupEvents
  },
  data: () => ({
      photo_src: "https://geodash.gov.bd/uploaded/people_group/default_group.png",
      group: {
        group_name: "Nome do Grupo",
        organizer_name: "João Antônio",
        organizer_contact: "(11) 11111-1111",
        interest: "Geografia",
      }
  }),
  methods: {
    entrar () {
      alert("Entrou no grupo")
    }
  }
}
</script>
<style>
.bigrect-group-name {
  margin-top: 30px;
  margin-bottom: 20px;
  margin-left: 170px;
}

.group_avatar {
  margin-left: 128px;
}

.vertical_spacer {
  margin-top: 115px;
}

.group-name-buttons {
  margin-top: 4px;
  margin-bottom: 4px;
}

</style>
