/************************************************************************************
 * Name        : app.js
 * Author      : Kaitlynn Prescott
 * Date        : Feb 16, 2017
 * Description : CS-564 Lab 4: Our First ToDo
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const todoItems = require("./todo");
const connection = require("./mongoConnection");

//createTask: 
let block1 = todoItems.createTask("Ponder Dinosaurs", "Has Anyone Really Been Far Even as Decided to Use Even Go Want to do Look More Like");

block1.then((taskItem1) => {
    console.log(taskItem1);
    let block2 = todoItems.createTask("Play Pokemon with Twitch TV", "Should we revive Helix?");
    block2.then((taskItem2) => {
        console.log(taskItem2);
        let taskGetter = todoItems.getAllTasks();
        let block3 = taskGetter.then((taskList) => {
            console.log(taskList);
            //removeTask:
            let taskRemover = todoItems.removeTask(taskList[0]._id);
            let taskGetter2 = todoItems.getAllTasks();
            let block4 = taskGetter2.then((allTasks2) => {
                console.log(allTasks2);
                //getTask:
                let taskGetter3 = todoItems.getTask(allTasks2[0]._id);
                let block5 = taskGetter3.then((taskItem3) => {
                	//completeTask:
                    return todoItems.completeTask(taskItem3._id);
                });
                block5.then((taskItem4) => {
                    console.log(taskItem4);
                    return connection();
                }).then((db) => {
                    return db.close();
                });
            });
        });
    });
});
