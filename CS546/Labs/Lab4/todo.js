/************************************************************************************
 * Name        : todo.js
 * Author      : Kaitlynn Prescott
 * Date        : Feb 16, 2017
 * Description : CS-564 Lab 4: Our First ToDo
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/
 
 
const mongoCollections = require("./mongoCollections");
const uuid = require("uuid");
const todoItems = mongoCollections.todoItems;
 
let exportedMethods = {
    createTask(title, description) {
        /* This function will return a promist that resolves to a newly created todo list object, with the following properties:
         * {
         *    _id: "a unique identifier for the task; you will generate these using uuid package",
         *    title: "the title of the task",
         *    description: "a descriptive bio of the task",
         *    completed: false,
         *    completedAt: null
         * }
         * The task will be stored in the todoItems mongoCollections
         * IMPORTANT NOTE: you will create and set the _id field in the createTask method.
         * IMPORTANT NOTE: as you can tell, the parameters only provide title and description. You must still set the other fields before inserting them into the database.
         * if the task cannot be created, method should reject.
         */
        if (!title) {
            return new Promise.reject("You must provide a title name.");
        }
        if (!description) {
            return new Promise.reject("You must provide a description.");
        }
        return todoItems().then((todoCollection) => {
            let todoItem = {
                _id: uuid.v1(),
                title: title,
                description: description,
                completed: false,
                completedAt: null
            };
            return todoCollection.insertOne(todoItem).then((newItem) => {
                return newItem.insertedID;
            }).then((newID) => {
                return this.getTask(newID);
            });
        });
    },
    getAllTasks() {
        /*
         * This function will return a promise that resolves to an array of all tasks in the database.
         */
         return new Promise((fulfill, reject) => {
             return todoItems().then((todoCollection) => {
                 return todoCollection.find({}).toArray((error, docs) => {
                     if (error) {
                         reject(error);
                     } else {
                         fulfill(docs);
                     }
                 });
             });
         });
    },
    getTask(id) {
        /*
         * This funciton will return a promise that resolves to a task from the database, when given an ID.
         * If no ID is provided, the method should return a rejected promise.
         * If the task does not exist, the method should return a rejected promise.
         */
        if (!id) {
            return Promise.reject("You must provide an ID to search for.");
        }
         return todoItems().then((todoCollection) => {
             return todoCollection.findOne({ _id: id });
         });
    },
    completeTask(taskId) {
        /* 
         * This function will modify the task in the database. It will set completed to true and completedAt to the current time.
         * If no id is provided, the method should return a rejected promise.
         * If the task cannot be updated or does not exist, the method should reject.
         * IMPORTANT NOTE: for now, in completedTask, you will want to get the task from the database, update the task in your JS code, and then run the update command.
         * If you would like to do something more advanced, you may also research using the $set command to accomplish this as well.
         */
        if (!taskId) {
            return Promise.reject("You must provide an ID to update.");
        }
        return todoItems().then((todoCollection) => {
            return todoCollection.findAndModify({ _id: taskId }, 
            [['_id', 'asc']], 
            {$set: 
                {
                    completed: true,
                    completedAt: new Date()
                }
            }, {}).then(() => {
                return this.getTask(taskId);
            });
        });
    },
    removeTask(id) {
        /*
         * This function will remove the task from the database.
         * If no ID is provided, the method should return a rejected promise.
         * If the task cannot be removed or does not exist, the method should return a rejected promise.
         */
        if (!id) {
            return Promise.reject("You must provide an ID to remove.");
        }
         return todoItems().then((todoCollection) => {
             return todoCollection.removeOne({ _id: id }).then((deletionInfo) => {
                 if (deletionInfo.deleteCount === 0) {
                     throw (`Could not delete task with ID of ${id}`);
                 } else {
                     console.log(`Deleted item with ID: ${id}`);
                 }
             });
         });
    }
}
 
module.exports = exportedMethods;