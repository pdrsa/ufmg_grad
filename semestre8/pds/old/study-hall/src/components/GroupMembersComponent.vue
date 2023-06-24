<template>
  <v-container>
    <v-card
      rounded="xl"
      color="#FFFFFF"
      elevation="10"
      max-width="800px"
      height="400px"
      class="bigrect-group-members"
    >

      <v-row>
        <h1 class="pa-8"> Membros </h1>
        <v-spacer></v-spacer>
      </v-row>

      <v-sheet
        class="ma-8"
        elevation="5"
        rounded
      >
        <v-slide-group>
          <v-slide-item
            v-for="(member) in members" :key="member.user_id"
            class="groupcards"
          >
            <v-card
              class="ma-4"
              height="180px"
              width="180px"
              elevation="1"
              outlined
              @click="open_profile(member.user_id)"
            >
              <v-card-text>
                <v-img :src="user_avatar"
                height="130px"
                width="130px"
                class="member_image"
                ></v-img>
                <h3 class="username">{{ member.username }}</h3>
              </v-card-text>
            </v-card>
          </v-slide-item>
        </v-slide-group>
      </v-sheet>

    </v-card>
  </v-container>
</template>
<script>
export default {
  data: () => ({
    user_avatar: "https://cdn.icon-icons.com/icons2/1378/PNG/512/avatardefault_92824.png",
    members: [
      {
        user_id: 1,
        username: "abobora"
      },
      {
        user_id: 2,
        username: "melancia"
      },
      {
        user_id: 3,
        username: "manga"
      },
      {
        user_id: 4,
        username: "banana"
      },
      {
        user_id: 5,
        username: "maçã"
      }
    ]
  }),
  methods: {
    open_profile (user_id) {
      alert("User ID desse usuário é " + user_id)

    }
  } 
}
</script>
<style>
.bigrect-group-members {
  margin-top: 30px;
  margin-bottom: 20px;
  margin-left: 170px;
}

.member_image {
  margin-left: 12px;
}

.username {
  text-align: center;
}
</style>
