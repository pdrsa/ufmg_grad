<template>
  <v-container>
    <v-card
      color="#FFFFFF"
      elevation=2
      height="800px"
      width="1188px"
      rounded="xl"
      class="bigrect-register-group"
    >
      <div>
        <v-row>
          <v-col
          cols="12"
          lg="8"
          class="pa-8" >
            <h1>Register Group</h1>
          </v-col>
        </v-row>
      </div>

      <v-row no-gutters>
        <v-col
        cols="12"
        lg="6"
        class="pa-8" >
          <v-text-field filled label="Group Name" v-model="group_name"></v-text-field>
        </v-col>
        <v-spacer></v-spacer>
        <v-col
        cols="12"
        lg="6"
        class="pa-8" >
          <v-select
            :items="items"
            filled
            label="Group's Subjects"
            v-model="interest"
          ></v-select>
        </v-col>
      </v-row>

      <v-row
        :align="align"
        no-gutters >
        <v-col
          cols="12"
          lg="6"
          class="pa-8" >
          <v-text-field filled label="Organizer Name" v-model="organizer_name"></v-text-field>
        </v-col>
        <v-spacer></v-spacer>
        <v-col
          cols="12"
          lg="6"
          class="pa-8" >
            <v-text-field filled label="Organizer Contact" v-model="organizer_contact"></v-text-field>
        </v-col>
      </v-row>

      <v-row
        :align="align"
        no-gutters >
       <v-col class="pa-8" >
          <v-textarea
           filled
           label="About Group"
           v-model="aboutMeContent"
           height="200px"></v-textarea>
         </v-col>
       </v-row>

      <div class="text-center">
         <v-btn
           height=84
           width=266
           color="primary"
           @click="postForm"
         >
         Register
         </v-btn>
      </div>
    </v-card>
  </v-container>
</template>

<script>
  import axios from 'axios';

  export default {
    data: () => ({
      items: ['Foo', 'Bar', 'Fizz', 'Buzz'],
      group_name: "",
      organizer_id: 0,
      organizer_name: "",
      organizer_contact: "",
      interest: "",
      aboutMeContent: ""      
    }),
    methods: {
      postForm() {
        const data = JSON.stringify({
          group_name: this.group_name,
          organizer_id: this.organizer_id,
          organizer_name: this.organizer_name,
          organizer_contact: this.organizer_contact,
          interest: this.interest,
          about: this.aboutMeContent
        })

        return axios.post("/add", {
            data: data
        }, {
            headers: {
                'Content-type': 'application/json',
            }
        }).then((response) => {
          console.log("content: " + response);
        });
      }
    }
  }
</script>

<style>
.hometext-register-group {
  border-right: 70px solid transparent;
  border-left: 70px solid transparent;
  border-top: 15px solid transparent;
  border-bottom: 15px solid transparent;
}

.buttonregister-register-group {
  background-color: #0D1A8F;
  color: white;
}

.bigrect-register-group {
  margin-top: 30px;
  margin-bottom: 20px;
  margin-left: -5px;
}

.uploading-image{
     display:flex;
   }
</style>
