var moviesOnScreen = 0;

function parseEntry(entry){
  var html = "<div class='search-entry'><div class='search-poster-div'><img src='" + (entry.Poster == "N/A" ? "media/movie-placeholder.jpg" : entry.Poster) + "' class='search-poster'></div><div><b>" + entry.Title + "</b> (" + entry.Year + ")</div></div><input type='hidden' value='" + entry.imdbID + "'>";
  return html;
}

function parseList(resp){
  var currentIMDBids = [];

  $(".movie").each(function(index){
    currentIMDBids.push($(this).find(".imdbid-hidden")[0].value);
  });

  var entries = [];
  if (resp.Response != "True") return ["Movie not found"];
  for (var i = 0; i < resp.Search.length; i++){
    if (currentIMDBids.indexOf(resp.Search[i].imdbID) == -1){
      entries.push(parseEntry(resp.Search[i]));
    }
  }

  //Limit to 7 entries
  while (entries.length > 7){
    entries.pop();
  }

  return entries;
}

function averageScore(rt, meta, imdb){
  var count = 0;
  var sum = 0;
  if (!isNaN(Number(rt))){
    count++;
    sum += Number(rt);
  }
  if (!isNaN(Number(meta))){
    count++;
    sum += Number(meta);
  }
  if (!isNaN(Number(imdb))){
    count++;
    sum += Number(imdb)*10;
  }
  if (count == 0){
    return "No ratings available."
  }

  return Math.round((sum) / count * 10) / 100;
}

function showYouTubeVideo(ytid){
  $("#comparisons").hide("clip", {}, "100");
  $("#trailer").show("clip", {}, "100");
  $("#trailer").find(".trailer-iframe-div").html("<iframe class='trailer-iframe' src='https://www.youtube.com/embed/" + ytid + "' frameborder='0' allowfullscreen></iframe>");

}

function hideYouTubeVideo(){
  console.log("hide");
  $("#trailer").hide("clip", {}, "100");
  $("#comparisons").show("clip", {}, "100");
  $("#trailer").find("iframe").remove();
}

//Suggest and highlight a movie to watch
//If multiple top picks, choose from among them
//If only one top pick, choose a random movie, but the top pick is more likely
function tieBreaker(){
  setLogoButtonEnabled(false);

  var topPicks = getTopPicks();

  if (topPicks.length > 1){
    //Multiple top picks, so choose from among them
    var chosenTopPick = Math.floor(Math.random() * topPicks.length);
    for (var i = 0; i < topPicks.length; i++){
      if (i == chosenTopPick){
        $(".movie").eq(i).find(".winner img").animate({width: "120px"}, 500);
      } else {
        $(".movie").eq(i).find(".winner").hide("fade", {}, 500, function(){
          $(".movie").eq(i).find(".winner img").css("width", "70px");
        });
      }
    }
  } else {
    //Only one top pick, so choose random movie
    var chosenMovie = Math.floor(Math.random() * ($(".movie").length + 1));

    //Make top pick more likely to be selected
    if (chosenMovie == $(".movie").length) chosenMovie = topPicks[0];

    if (topPicks[0] == chosenMovie){
      //Chosen movie is the top pick
      $(".movie").eq(chosenMovie).find(".winner").animate({width: "75px", height: "30px", fontSize: "16pt"}, 500);

    } else {
      //Chosen movie is not the top pick
      //Slide the winner badge from the top pick to the chosen movie

      var originalLeft = $(".movie").eq(topPicks[0]).offset().left;
      var destinationLeft = $(".movie").eq(chosenMovie).offset().left;

      $(".movie").eq(topPicks[0]).find(".winner").css("left", originalLeft + "px");
      $(".movie").eq(topPicks[0]).find(".winner").animate({left: destinationLeft + "px"}, 500, function(){
        $(".movie").eq(chosenMovie).find(".winner").show();
        $(".movie").eq(topPicks[0]).find(".winner").hide();
        $(".movie").eq(topPicks[0]).find(".winner").css("left", "");
      });

    }

  }
}

function getTopPicks(){
  if ($(".movie").length < 2) return [];

  var max = 0;
  var maxindex = -1;
  $(".movie").each(function(index){
    var total = Number($(this).find(".total-score-span").text());
    if (total > max){
      max = total;
      maxindex = index;
    }
  });
  var topPicks = [];

  $(".movie").each(function(index){
    var total = Number($(this).find(".total-score-span").text());
    if (total >= (max - 0.09)){
      topPicks.push(index);
    }
  });

  return topPicks;
}

function setLogoButtonEnabled(value){
  if (value){
    //Make the logo a link
    $("#title a").attr("href", "javascript:tieBreaker();");
    $("#title a").hover(
      function(){ //Function for mouse moved onto logo
        $(this).css("text-shadow", "0px 0px 15px #fff");
      },
      function(){ ///Function for mouse moved off of logo
        $(this).css("text-shadow", "");
      }
    );
    $("#title").addClass("pulsate");
  } else {
    $("#title a").unbind("mouseenter mouseleave")
                 .css("text-shadow", "")
                 .removeAttr("href");
    $("#title").removeClass("pulsate");
  }

}

/*
function ytTrailer(searchTerm){
//verifies that trailer exists
}
*/

function updateWinners(){
  var topPicks = getTopPicks();
  //Add badge to top picks
  for (var i = 0; i < $(".movie").length; i++){
    if (topPicks.indexOf(i) != -1){
      $(".movie").eq(i).find(".winner").show();
    } else {
      //$(".movie").eq(i).find(".winner").hide();
    }
  }
}

function loadIntoCard(nextCard, moviedata){
  //Report tracking info to Google Analytics
  ga('send', {
    hitType: 'event',
    eventCategory: 'Movie',
    eventAction: 'Add',
    eventLabel: moviedata.Title + " (" + moviedata.Year + ")"
  });

  nextCard.find(".loading-div-inner").hide("clip", {}, 400, function(){
    nextCard.find(".info-div").show("blind", {}, 400);
  });

  nextCard.find(".imdbid-hidden").attr("value", moviedata.imdbID);
  nextCard.find(".poster-div").html("<img class='poster-image' src='" + (moviedata.Poster == "N/A" ? "media/movie-placeholder.jpg" : moviedata.Poster) + "'>");
  nextCard.find(".title-span").text(moviedata.Title);
  nextCard.find(".year-span").text(moviedata.Year);
  if (moviedata.tomatoMeter != "N/A"){
    rtScore = Number(moviedata.tomatoMeter) / 10;
    nextCard.find(".rt-score-span").text(rtScore.toFixed(1));
  } else {
    nextCard.find(".rt-score-span").closest("tr").hide();
  }

  if (moviedata.Metascore != "N/A"){
    metascore = Number(moviedata.Metascore) / 10;
    nextCard.find(".meta-score-span").text(metascore.toFixed(1));
  } else {
    nextCard.find(".meta-score-span").closest("tr").hide();
  }
  if (moviedata.imdbRating != "N/A"){
    nextCard.find(".imdb-score-span").text(moviedata.imdbRating);
  } else {
    nextCard.find(".imdb-score-span").closest("tr").hide();
  }
  nextCard.find(".total-score-span").text(averageScore(moviedata.tomatoMeter, moviedata.Metascore, moviedata.imdbRating).toFixed(2));

  nextCard.find(".awards-span").html(moviedata.Awards.split(".").join(".<br>"));

  nextCard.find(".description-span").text(moviedata.Plot);


//LOAD TRAILER FROM YOUTUBE SEARCH
  var trailerQuery = "q="+moviedata.Title+ " " + moviedata.Year + " trailer ";
  /*if (ytTrailer(trailer) == true){*/
  var ytApi = "https://www.googleapis.com/youtube/v3/search?&part=snippet&";

  // add trailer search to url
  ytApi += trailerQuery;

  // set paid-content as false to hide movie rentals
  ytApi += '&paid-content=false';

  // order search results by view count
  ytApi += '&orderby=viewCount';

  // we can request a maximum of 50 search results in a batch
  ytApi += '&max-results=5';

  //add API key to request
  ytApi += "&key=AIzaSyB7fviQwRX7IwuQ4xM1JiosM-t-tmSNG6s";

  $.ajax({
    url: ytApi,
    dataType: "jsonp",
    success: function(data){
      nextCard.find(".trailer-button").prop('disabled', false);
      nextCard.find(".trailer-button").click(function(){
        showYouTubeVideo(data.items[0].id.videoId);
      });
    }
  });
//LOAD REDDIT DISCUSSION THREAD FROM REDDIT SEARCH
  var redditQuery = "q="+moviedata.Title+ " official discussion";
  var redditApi = "https://reddit.com/r/movies/search.json?restrict_sr=on&";

  //add search query to url
  redditApi+=redditQuery;

  $.ajax({
    url: redditApi,
    dataType: "jsonp",
	jsonp: "jsonp",
    success: function(data){
      var children = data.data.children;
      nextCard.find(".discussion-loading-img").hide();
      nextCard.find(".spoiler").show();
      if (children.length > 0 && (children[0].data.link_flair_text.indexOf("Discussion") != -1 || children[0].data.title.toLowerCase().indexOf("official discussion") != -1) && children[0].data.id != "2p3ite"){
        nextCard.find(".reddit-a").show();
        nextCard.find(".reddit-a").attr("href", data.data.children[0].data.url);
      }
    }
  });


  moviesOnScreen++;

  if ($(".movie").length >= 2){
    updateWinners();
    setLogoButtonEnabled(true);
  }
}

function loadMovie(imdbID){
  var callbacksRemaining = 2;
  var movieData = {};

  var nextCard;
  if (moviesOnScreen == 0){ //First card
    nextCard = $(".movie").eq(0);
    nextCard.css("display","inline-block");
    $("#comparisons").show("clip", {}, "100");
    callbacksRemaining--; //card not animating so don't need to wait for callback
    if (callbacksRemaining == 0) loadIntoCard(nextCard, movieData);
  } else { //Not first card, so clone the previous card
    nextCard = $(".movie").last().clone(true, true);
    nextCard.hide()
            .insertAfter($(".movie").last())
            .show(400, function(){
              callbacksRemaining--;
              if (callbacksRemaining == 0) loadIntoCard(nextCard, movieData);
            });
  }

  //Clean up card to prepare information to be loaded into it
  nextCard.find(".info-div").hide();
  nextCard.find(".loading-div-inner").show();
  nextCard.find(".rt-score-span").closest("tr").show();
  nextCard.find(".meta-score-span").closest("tr").show();
  nextCard.find(".imdb-score-span").closest("tr").show();
  //nextCard.find(".winner").hide();
  nextCard.find(".trailer-button").off("click");
  nextCard.find(".trailer-button").prop('disabled', true);
  nextCard.find(".spoiler").hide();
  nextCard.find(".reddit-a").removeAttr("href");
  nextCard.find(".reddit-a").hide();
  nextCard.find(".discussion-loading-img").show();

  //Start loading information from API
  //Information will not be loaded into card until card is finished animating
  $.ajax({
    url: "https://omdbapi.com/?i=" + imdbID + "&tomatoes=true&plot=short",
    dataType: "jsonp",
    success: function(data){
      movieData = data;
      callbacksRemaining--;
      if (callbacksRemaining == 0) loadIntoCard(nextCard, movieData);
    }
  });
}

$(document).ready(function(){
  $("#query").on("input", function(){
    $("#search-bar").animate({height:"60px"}, 200);
  });
  $("#query").autocomplete({
    source: function(request, response){
      //Show loading gif in input box
      $("#query").css("background", "white url('media/loading.gif') no-repeat right");
      $("#query").css("background-position", "calc(100% - 10px)");
      $.ajax({
        url: "https://omdbapi.com/?s=" + request.term.trim() + "*",
        dataType: "jsonp",
        success: function(data){
          response(parseList(data));
          //Hide loading gif in input box
          $("#query").css("background", "white");
        }
      });
    },
    select: function(event, ui){
      //stops API call from being added to search box
      event.preventDefault();

      function sendAPICall(){
        loadMovie($.parseHTML(ui.item.value)[1].value);
      }

      if (moviesOnScreen >= 4){
        $("#add-movie").hide(400, sendAPICall); //If adding fifth card, hide "add movie" card
        $("#query").attr("disabled", "disabled");
        $("#query").css("background", "#aaa");
        $("#query").css("border-color", "#aaa");
      } else {
        sendAPICall();
      }

      //clears text from search box
      $("#query").val("");
    }
  }).data("ui-autocomplete")._renderItem = function (ul, item) {
    return $("<li></li>").data("item.autocomplete", item).append("<a>" + item.label + "</a>").appendTo(ul);
  };

  //Bind event to delete buttons (trash can)
  $(".delete-a").click(function(){
    var card = $(this).closest(".movie");
    card.find(".imdbid-hidden").attr("value", ""); //This is to allow the movie to be selected again
    card.hide(400, function(){
      moviesOnScreen--;
      if (moviesOnScreen > 0) card.remove();
      if (moviesOnScreen < 2) setLogoButtonEnabled(false);
      if (moviesOnScreen < 5){
        $("#add-movie").show(400);
        $("#query").removeAttr("disabled");
        $("#query").css("background", "white");
        $("#query").css("border-color", "#eee");
      }
      updateWinners();
    });
  });

  //Bind event to trailer close buttons
  $(".trailer-close-a").click(hideYouTubeVideo);

  //Bind event to "add movie" card
  $("#add-movie").click(function(){
    $("#query")[0].focus();
  });

});

/*
function checkVisited(){
  //<script src="js.cookie.js"></script> in HTML
  //https://github.com/js-cookie/js-cookie
  if(Cookies.get('visited'==undefined){//no cookie
    alert("Hey this is a test message, it looks like you haven't been here before.");
    Cookies.set('visited', 'true', {expires: 1000000});//you need to set a value for it not to be a session cookie
  }
}
*/
